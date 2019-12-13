using SpriteEditor;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace WindowEditor
{
	public partial class MainWindowEditor : Form
    {
        public enum Action { WindowAdd, WindowEdit, WindowResize}

        private DoubleBufferPanel _doubleBufferPanel = new DoubleBufferPanel();
        private string _filename;
        private Sprite sprite;
        private Image _currentIcon;
        private string _currentDesignKey;
        private int _currentDesignIndex;

		private Window _root;

		private Window _showingWindow;
		public Window ShowingWindow
		{
			get
			{
				return this._showingWindow;
			}
			private set
			{
				this._showingWindow = value;
				this._doubleBufferPanel.Invalidate();
			}
		}

		private Window _selectedWindow;
		private Window _hoverWindow;
		private bool _resizeLeft, _resizeTop, _resizeRight, _resizeBottom;
		private Point _begin;
		private bool _editable;

		private TreeNode ShowingWindowNode
		{
			get
			{
				return this.GetShowingWindowNode(this.windowStructView.Nodes);
			}
		}

		private TreeNode GetShowingWindowNode(TreeNodeCollection root)
		{
			foreach (TreeNode node in root)
			{
				var window = node.Tag as Window;
				if (window == this.ShowingWindow)
					return node;

				var nodeChild = this.GetShowingWindowNode(node.Nodes);
				if (nodeChild != null)
					return nodeChild;

			}

			return null;
		}

		public float ScaleRatio
        {
            get
            {
                return this.scaleTrackBar.Value / 10.0f;
            }
        }

        private int scaleSize(int value)
        {
            return (int)(value * this.ScaleRatio);
        }

        private Point scaleSize(Point value)
        {
            return new Point((int)(value.X * this.ScaleRatio), (int)(value.Y * this.ScaleRatio));
        }

        private Sprite loadSprite(string filename)
        {
            sprite = new Sprite(filename);
            this.windowDesignImageList.Images.Clear();
            foreach (var pair in sprite)
            {
                using (var stream = new MemoryStream(pair.Value.Bytes))
                {
                    var image = Image.FromStream(stream);
                    this.windowDesignImageList.Images.Add(pair.Key, image);
                }
            }
            this.windowDesignListView.LargeImageList = this.windowDesignImageList;

            this.windowDesignListView.Clear();

            var imageIndex = 0;
            foreach (var pair in sprite)
                this.windowDesignListView.Items.Add(pair.Key, pair.Key).Tag = imageIndex++;

            return sprite;
        }

        private void initialize(int width, int height, string spriteFileName)
        {
            this._currentIcon = null;
            this._currentDesignKey = null;
            this._currentDesignIndex = -1;
            this._filename = null;
            this.windowDesignImageList.Images.Clear();
            this.windowDesignListView.Items.Clear();
			this.windowStructView.Nodes.Clear();

            this._root = new Window(string.Empty, string.Empty, null, 0, 0, width, height, "Window", string.Empty, true, this.loadSprite(spriteFileName));
			this.ShowingWindow = this._root;

			var node = this.windowStructView.Nodes.Add("root", "root", -1);
			node.Tag = this._root;
			this.windowStructView.SelectedNode = node;
		}

		private TreeNode BindStructView(Window window, TreeNode root = null)
		{
			var node = null as TreeNode;
			if (root == null)
			{
				this.windowStructView.Nodes.Clear();
				node = this.windowStructView.Nodes.Add("root", "root", -1);
			}
			else
			{
				node = root.Nodes.Add(window.Id, window.Id);
			}
			node.Tag = window;
			foreach (var control in window.Controls)
				this.BindStructView(control, node);

			return node;
		}

        public MainWindowEditor()
        {
            InitializeComponent();

            this._doubleBufferPanel.Dock = DockStyle.Fill;
            this._doubleBufferPanel.Paint += this.canvasPanel_Paint;
            this._doubleBufferPanel.MouseDown += this.canvasPanel_MouseDown;
            this._doubleBufferPanel.MouseMove += this.canvasPanel_MouseMove;
            this._doubleBufferPanel.MouseUp += this.canvasPanel_MouseUp;
            this.splitContainer.Panel1.Controls.Add(this._doubleBufferPanel);
        }

        private void WindowDesignListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedItems = this.windowDesignListView.SelectedItems;

            if (selectedItems.Count == 0)
                return;

            var selectedName = selectedItems[0].Text;
            var selectedIndex = selectedItems[0].Index;
            using (var stream = new MemoryStream(this._root.Sprite[selectedName].Bytes))
            {
                this._currentIcon = Image.FromStream(stream);
                this._currentDesignKey = selectedName;
                this._currentDesignIndex = selectedIndex;
            }
            
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            try
            {
                var dialog = new MainWindowAttrDialog();
                if (dialog.ShowDialog() != DialogResult.OK)
                    throw new Exception();

                var spriteDialog = new OpenFileDialog();
                spriteDialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
                if (spriteDialog.ShowDialog() != DialogResult.OK)
                    throw new Exception();

                this.initialize(dialog.WindowWidth, dialog.WindowHeight, spriteDialog.FileName);
            }
            catch (Exception exc)
            {
                Application.Exit();
            }
        }

        private void canvasPanel_MouseDown(object sender, MouseEventArgs e)
        {
			try
			{
				if (this._editable)
				{
					this._hoverWindow = this.hoverWindow(e.Location, out this._resizeLeft, out this._resizeRight, out this._resizeTop, out this._resizeBottom);
					if (this._hoverWindow != null)
					{
						this._begin = e.Location;
					}
				}

				else
				{
					var wIndex = (int)(e.X / this.ScaleRatio);
					var hIndex = (int)(e.Y / this.ScaleRatio);

					if (wIndex >= this._showingWindow.Size.Width || hIndex >= this._showingWindow.Size.Height)
						return;

					if (e.Button == MouseButtons.Left)
					{

						var dialog = new SubWindowAttrDialog();
                        dialog.WindowX = wIndex;
                        dialog.WindowY = hIndex;
						if (dialog.ShowDialog() != DialogResult.OK)
							return;

                        var designKey = dialog.WindowUseImage == true ? this._currentDesignKey : string.Empty;

						try
						{
                            var createdWindow = new Window(dialog.WindowId, designKey, this._showingWindow, wIndex, hIndex, dialog.WindowWidth, dialog.WindowHeight, dialog.WindowPurpose, dialog.WindowText, dialog.WindowInvisible, this.sprite);

                            if (this.windowStructView.SelectedNode == null)
								throw new Exception("부모 윈도우를 선택해야 합니다.");
                            
                            var treenode = this.windowStructView.Nodes.Find(createdWindow.Id, true);
                            if (treenode.Length != 0)
                                throw new Exception("다른 ID 값을 설정해주어야 합니다.");

							// 쇼잉 윈도우의 자식 Node로 추가해야 하는데, 지금은 selectedWindow의 자식으로 추가하고 있어서
							// window가 아닌 놈을 클릭하고 무언가 추가하면, purpose가 window가 아니더라도 자식을 갖는 구조임.
							var showingWindowNode = this.ShowingWindowNode;
							if (showingWindowNode == null)
								throw new Exception("선택할 수 있는 노드가 없습니다.");

                            var node = showingWindowNode.Nodes.Add(createdWindow.Id, createdWindow.Id, this._currentDesignIndex);
							node.Tag = createdWindow;

							this._showingWindow.Controls.Add(createdWindow);
						}
						catch (Exception exc)
						{
							MessageBox.Show(this, exc.Message);
						}
					}

					this._doubleBufferPanel.Invalidate();
				}
			}
			catch (Exception exc)
			{
				MessageBox.Show(this, exc.Message);
			}
        }

		private Window hoverWindow(Point location, out bool left, out bool right, out bool top, out bool bottom)
		{
			var absoluteLocation = new Point((int)(location.X / this.ScaleRatio), (int)(location.Y / this.ScaleRatio));
			var limit = 0.1f;
			var cursor = Cursors.Default;

			left = false;
			right = false;
			top = false;
			bottom = false;

			foreach (var control in this._showingWindow.Controls)
			{
				var areaTop = new Rectangle(new Point(control.Location.X, (int)(control.Location.Y - control.Size.Height * limit)), new Size(control.Size.Width, (int)(control.Size.Height * limit * 2)));
				var areaBot = new Rectangle(new Point(control.Location.X, (int)(control.Location.Y + control.Size.Height - control.Size.Height * limit)), new Size(control.Size.Width, (int)(control.Size.Height * limit * 2)));
				var areaLeft = new Rectangle(new Point((int)(control.Location.X - control.Size.Width * limit), control.Location.Y), new Size((int)(control.Size.Width * limit * 2), control.Size.Height));
				var areaRight = new Rectangle(new Point((int)(control.Location.X + control.Size.Width - control.Size.Width * limit), control.Location.Y), new Size((int)(control.Size.Width * limit * 2), control.Size.Height));
				if (areaTop.Contains(absoluteLocation))
				{
					top = true;
					return control;
				}
				else if (areaBot.Contains(absoluteLocation))
				{
					bottom = true;
					return control;
				}
				else if (areaLeft.Contains(absoluteLocation))
				{
					left = true;
					return control;
				}
				else if (areaRight.Contains(absoluteLocation))
				{
					right = true;
					return control;
				}
				else if (new Rectangle(control.Location, control.Size).Contains(absoluteLocation))
				{
					return control;
				}
			}

			return null;
		}

        private void canvasPanel_MouseMove(object sender, MouseEventArgs e)
        {
			if (this._hoverWindow == null)
			{
				bool left, top, right, bottom;
				var hovered = this.hoverWindow(e.Location, out left, out right, out top, out bottom);
				if (hovered == null)
					this.Cursor = Cursors.Default;

				if (left || right)
					this.Cursor = Cursors.SizeWE;

				else if (top || bottom)
					this.Cursor = Cursors.SizeNS;

				else
					this.Cursor = Cursors.Default;

				this._editable = (hovered != null);
			}
			else
			{
				var increase = new Point((int)((e.X - this._begin.X) / this.ScaleRatio), (int)((e.Y - this._begin.Y) / this.ScaleRatio));
				if (this._resizeLeft)
				{
					this._hoverWindow.Size = new Size(this._hoverWindow.Size.Width - increase.X, this._hoverWindow.Size.Height);
					this._hoverWindow.Location = new Point(this._hoverWindow.Location.X + increase.X, this._hoverWindow.Location.Y);
				}
				else if (this._resizeTop)
				{
					this._hoverWindow.Size = new Size(this._hoverWindow.Size.Width, this._hoverWindow.Size.Height - increase.Y);
					this._hoverWindow.Location = new Point(this._hoverWindow.Location.X, this._hoverWindow.Location.Y + increase.Y);
				}
				else if (this._resizeRight)
				{
					this._hoverWindow.Size = new Size(this._hoverWindow.Size.Width + increase.X, this._hoverWindow.Size.Height);
				}
				else if (this._resizeBottom)
				{
					this._hoverWindow.Size = new Size(this._hoverWindow.Size.Width, this._hoverWindow.Size.Height + increase.Y);
				}
				else
				{
					this._hoverWindow.Location = new Point(this._hoverWindow.Location.X + increase.X, this._hoverWindow.Location.Y + increase.Y);
				}

				this._begin = e.Location;
				this._doubleBufferPanel.Invalidate();
			}
		}

        private void canvasPanel_Paint(object sender, PaintEventArgs e)
        {
            this.drawGrid(e.Graphics);
            this.drawWindows(e.Graphics, this._root.Location, this.ShowingWindow);
        }

        private void scaleTrackBar_Scroll(object sender, EventArgs e)
        {
            this._doubleBufferPanel.Invalidate();
        }

		private void drawWindows(Graphics g, Point absoluteLocation, Window window)
		{
			foreach (var item in window.Controls)
			{
				var spriteName = item.SpriteName.ToString();

				
                var area = new Rectangle(
                        new Point(this.scaleSize(absoluteLocation.X + item.Location.X), this.scaleSize(absoluteLocation.Y + item.Location.Y)),
                        new Size(this.scaleSize(item.Size.Width), this.scaleSize(item.Size.Height)));

                if (spriteName == string.Empty)
                {
                    g.DrawRectangle(Pens.Blue, area);
                    //SolidBrush blueBrush = new SolidBrush(Color.Blue);
                    //g.FillRectangle(blueBrush, area);
                }
                else
                {
                    using (var stream = new MemoryStream(this._root.Sprite[spriteName].Bytes))
                    {
                        var image = Image.FromStream(stream);
                        g.DrawImage(image, area);
                    }
                }

                area.Y = ((area.Bottom + area.Top) / 2) - 2;
                g.DrawString(item.Text, SystemFonts.DefaultFont, Brushes.Black, area);


                this.drawWindows(g, new Point(absoluteLocation.X + item.Location.X, absoluteLocation.Y + item.Location.Y), item);
			}
		}

        private void drawGrid(Graphics g)
        {
            g.DrawLine(Pens.Black, new Point((int)(this._showingWindow.Size.Width * this.ScaleRatio), 0), new Point((int)(this._showingWindow.Size.Width * this.ScaleRatio), (int)(this._showingWindow.Size.Height * this.ScaleRatio)));

            g.DrawLine(Pens.Black, new Point(0, (int)(this._showingWindow.Size.Height * this.ScaleRatio)), new Point((int)(this._showingWindow.Size.Width * this.ScaleRatio), (int)(this._showingWindow.Size.Height * this.ScaleRatio)));
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
			try
			{
				if (this._filename == null)
				{
					var dialog = new SaveFileDialog();
					dialog.DefaultExt = "pbw";
					dialog.Filter = "PB Window file (*.pbw)|*.pbw";

					if (dialog.ShowDialog() != DialogResult.OK)
						return;

					this._filename = dialog.FileName;
				}
				using (var writer = new BinaryWriter(File.Open(this._filename, FileMode.Create)))
				{
					this._root.Save(writer);
				}
			}
			catch (Exception exc)
			{
				MessageBox.Show(this, exc.Message);
			}
		}

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
			try
			{
				var dialog = new SaveFileDialog();
				dialog.DefaultExt = "pbw";
				dialog.Filter = "PB Window file (*.pbw)|*.pbw";

				if (dialog.ShowDialog() != DialogResult.OK)
					return;

				using (var writer = new BinaryWriter(File.Open(this._filename, FileMode.Create)))
				{
					this._root.Save(writer);
				}
			}
			catch (Exception exc)
			{
				MessageBox.Show(this, exc.Message);
			}
		}

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
			var dialog = new OpenFileDialog();
			dialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			sprite = this.loadSprite(dialog.FileName);

			dialog.Filter = "PB Window file(*.pbw)|*.pbw";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			using (var reader = new BinaryReader(File.Open(dialog.FileName, FileMode.Open)))
			{
				this._root = new Window(sprite, reader, null);
				this._showingWindow = this._root;
			}

			this.windowStructView.SelectedNode = this.BindStructView(this._root);

			this._filename = dialog.FileName;
			this._doubleBufferPanel.Invalidate();
			MessageBox.Show(this, "로드했음");
		}

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dialog = new MainWindowAttrDialog();
            if (dialog.ShowDialog() != DialogResult.OK)
                return;

            var spriteDialog = new OpenFileDialog();
            spriteDialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
            if (spriteDialog.ShowDialog() != DialogResult.OK)
                return;

            this.initialize(dialog.WindowWidth, dialog.WindowHeight, spriteDialog.FileName);
            this._doubleBufferPanel.Invalidate();
        }

        private void windowStructView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            var dialog = new SubWindowAttrDialog(this._selectedWindow);
            if (dialog.ShowDialog() != DialogResult.OK)
                return;

            this._selectedWindow.Location = new Point(dialog.WindowX, dialog.WindowY);
            this._selectedWindow.Size = new Size(dialog.WindowWidth, dialog.WindowHeight);
            this._selectedWindow.Id = dialog.WindowId;
            this._selectedWindow.Text = dialog.WindowText;
            this._selectedWindow.SpriteName = dialog.WindowUseImage ? this._selectedWindow.SpriteName : string.Empty;
            this._selectedWindow.Purpose = dialog.WindowPurpose;
            this._selectedWindow.isVisible = dialog.WindowInvisible;

            this._doubleBufferPanel.Invalidate();
        }

        private void canvasPanel_MouseUp(object sender, MouseEventArgs e)
        {
			this._hoverWindow = null;
        }

		private void windowStructView_AfterSelect(object sender, TreeViewEventArgs e)
		{
			var selectedNode = this.windowStructView.SelectedNode;
			if (selectedNode == null)
				return;

			this._selectedWindow = selectedNode.Tag as Window;
			if (this._selectedWindow.Purpose.Equals("Window"))
				this.ShowingWindow = this._selectedWindow;
		}

		private void windowStructView_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Delete)
			{
				var selectedNode = this.windowStructView.SelectedNode;
				if (selectedNode == null || selectedNode.Parent == null)
					return;

				var selectedWindow = selectedNode.Tag as Window;
				selectedNode.Remove();
				this._showingWindow.Controls.Remove(selectedWindow);

				this._doubleBufferPanel.Invalidate();
			}
		}
	}
}
