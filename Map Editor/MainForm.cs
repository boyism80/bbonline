using SpriteEditor;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace MapEditor
{
	public partial class MainForm : Form
	{
		public enum Action { MapTile, RespawnPoint, Enemy, }

		private DoubleBufferPanel _doubleBufferPanel = new DoubleBufferPanel();
		private string _filename;
		private Map _map;
		private Action _action;

		private Image _currentIcon;
		private string _currentTileKey;

		private Point CurrentPoint
		{
			get; set;
		}

		private Point InGamePoint
		{
			get
			{
				var x = (int)(this.CurrentPoint.X / this.ScaleRatio);
				var y = (int)(this.CurrentPoint.Y / this.ScaleRatio);

				return new Point(x, y);
			}
		}

		private Point AdjustedInGamePoint
		{
			get
			{
				var inGamePoint = this.InGamePoint;
				var x = (inGamePoint.X / this._map.TileSize.Width) * this._map.TileSize.Width;
				var y = (inGamePoint.Y / this._map.TileSize.Height) * this._map.TileSize.Height;

				return new Point(x, y);
			}
		}

		public byte Flags
		{
			get
			{
				var left = this.collisionLeft.Checked ? (byte)Map.Tile.Flag.Left : 0;
				var right = this.collisionRight.Checked ? (byte)Map.Tile.Flag.Right : 0;
				var top = this.collisionTop.Checked ? (byte)Map.Tile.Flag.Top : 0;
				var bottom = this.collisionBottom.Checked ? (byte)Map.Tile.Flag.Bottom : 0;

				return (byte)(left | right | top | bottom);
			}
		}


		// 리스폰 포인트
		private int _currentRespawnPointIndex = -1;


		// 적군
		private string _currentEnemyName;

		private bool _isLButtonDown = false, _isRButtonDown = false;

		public float ScaleRatio
		{
			get
			{
				return this.scaleTrackBar.Value / 10.0f;
			}
		}

		public MainForm()
		{
			InitializeComponent();

			this._doubleBufferPanel.Dock = DockStyle.Fill;
			this._doubleBufferPanel.Paint += this.canvasPanel_Paint;
			this._doubleBufferPanel.MouseMove += this.canvasPanel_MouseMove;
			this._doubleBufferPanel.MouseDown += this.canvasPanel_MouseDown;
			this._doubleBufferPanel.MouseUp += this.canvasPanel_MouseUp;
			this.splitContainer.Panel1.Controls.Add(this._doubleBufferPanel);
			this._doubleBufferPanel.BringToFront();
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
			var sprite = new Sprite(filename);
			this.mapTileImageList.Images.Clear();
			foreach (var pair in sprite)
			{
				using (var stream = new MemoryStream(pair.Value.Bytes))
				{
					var image = Image.FromStream(stream);
					this.mapTileImageList.Images.Add(pair.Key, image);
				}
			}
			this.mapTileListView.LargeImageList = this.mapTileImageList;
			this.mapTileListView.Clear();

			var imageIndex = 0;
			foreach (var pair in sprite)
				this.mapTileListView.Items.Add(pair.Key, pair.Key).Tag = imageIndex++;

			return sprite;
		}

		private void initialize(int rows, int cols, int tileWidth, int tileHeight, string spriteFileName)
		{
			this._currentIcon = null;
			this._currentTileKey = null;
			this._filename = null;
			this._isLButtonDown = this._isRButtonDown = false;
			this.mapTileImageList.Images.Clear();
			this.mapTileListView.Items.Clear();
			this._map = new Map(null, rows, cols, tileWidth, tileHeight, this.loadSprite(spriteFileName));
		}

		private void updateStateView()
		{
			this.mapSizeLabel.Text = string.Format("{0}x{1}", this._map.Rows, this._map.Columns);
			this.tileSizeLabel.Text = string.Format("{0}x{1}", this._map.TileSize.Width, this._map.TileSize.Height);
		}

		private void drawGrid(Graphics g)
		{
			// Draw grid
			for (var col = 0; col < this._map.Columns + 1; col++)
				g.DrawLine(Pens.Black, new Point(col * this.scaleSize(this._map.TileSize.Width), 0), new Point(col * this.scaleSize(this._map.TileSize.Width), this._map.Rows * this.scaleSize(this._map.TileSize.Height)));

			for (var row = 0; row < this._map.Rows + 1; row++)
				g.DrawLine(Pens.Black, new Point(0, row * this.scaleSize(this._map.TileSize.Height)), new Point(this._map.Columns * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height)));
		}

		private void drawTiles(Graphics g)
		{
			for (var row = this._map.Rows - 1; row >= 0; row--)
			{
				for (var col = 0; col < this._map.Columns; col++)
				{
					var tile = this._map[row, col];
					if (tile == null)
						continue;

					var spriteName = tile.Value.id.ToString();

					using (var stream = new MemoryStream(this._map.Sprite[spriteName].Bytes))
					{
						var image = Image.FromStream(stream);
						var area = new Rectangle(col * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height), this.scaleSize(image.Width), this.scaleSize(image.Height));
						area.Y -= this.scaleSize(image.Height) - this.scaleSize(this._map.TileSize.Height);
						g.DrawImage(image, area);
					}
				}
			}

			for (var row = 0; row < this._map.Rows; row++)
			{
				for (var col = 0; col < this._map.Columns; col++)
				{
					var tile = this._map[row, col];
					if (tile == null)
						continue;

					var flag = (int)tile.Value.flag;
					if ((flag & (int)Map.Tile.Flag.Left) == (int)Map.Tile.Flag.Left)
					{
						g.DrawLine(Pens.Red, new Point(col * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height)), 
							new Point(col * this.scaleSize(this._map.TileSize.Width), (row + 1) * this.scaleSize(this._map.TileSize.Height)));
					}

					if ((flag & (int)Map.Tile.Flag.Right) == (int)Map.Tile.Flag.Right)
					{
						g.DrawLine(Pens.Red, new Point((col + 1) * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height)),
							new Point((col + 1) * this.scaleSize(this._map.TileSize.Width), (row + 1) * this.scaleSize(this._map.TileSize.Height)));
					}

					if ((flag & (int)Map.Tile.Flag.Top) == (int)Map.Tile.Flag.Top)
					{
						g.DrawLine(Pens.Red, new Point(col * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height)),
							new Point((col + 1) * this.scaleSize(this._map.TileSize.Width), row * this.scaleSize(this._map.TileSize.Height)));
					}

					if ((flag & (int)Map.Tile.Flag.Bottom) == (int)Map.Tile.Flag.Bottom)
					{
						g.DrawLine(Pens.Red, new Point(col * this.scaleSize(this._map.TileSize.Width), (row + 1) * this.scaleSize(this._map.TileSize.Height)),
							new Point((col + 1) * this.scaleSize(this._map.TileSize.Width), (row + 1) * this.scaleSize(this._map.TileSize.Height)));
					}
				}
			}
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			try
			{
				var dialog = new MapAttrDialog();
				if (dialog.ShowDialog() != DialogResult.OK)
					throw new Exception();

				var spriteDialog = new OpenFileDialog();
				spriteDialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
				if (spriteDialog.ShowDialog() != DialogResult.OK)
					throw new Exception();

				this.initialize(dialog.Rows, dialog.Columns, dialog.TileWidth, dialog.TileHeight, spriteDialog.FileName);
				this.updateStateView();
			}
			catch (Exception exc)
			{
				Application.Exit();
			}
		}

		private void canvasPanel_Paint(object sender, PaintEventArgs e)
		{
			this.drawGrid(e.Graphics);
			this.drawTiles(e.Graphics);

			if (this._currentIcon != null)
			{
				var area = new Rectangle(this.scaleSize(this.AdjustedInGamePoint.X), this.scaleSize(this.AdjustedInGamePoint.Y),
										 this.scaleSize(this._map.TileSize.Width),
										 this.scaleSize(this._map.TileSize.Height));
				e.Graphics.DrawImage(this._currentIcon, area);
			}

			for (var i = 0; i < this._map.RespawnPoints.Length; i++)
			{
				if (this._map.RespawnPoints[i] == null)
					continue;

				var icon = this.respawnPointImageList.Images[i];
				var point = new Point(this.scaleSize(this._map.RespawnPoints[i].Value.X), this.scaleSize(this._map.RespawnPoints[i].Value.Y));
				var size = new Size(this.scaleSize(this._map.TileSize.Width), this.scaleSize(this._map.TileSize.Height));

				point.X -= (int)(size.Width / 2.0f);
				point.Y -= size.Height;
				e.Graphics.DrawImage(icon, new Rectangle(point, size));
			}

			foreach (var enemy in this._map.Enemies)
			{
				var index = this.enemyListView.Items[enemy.name].ImageIndex;
				var icon = this.enemyImageList.Images[index];
				var point = new Point(this.scaleSize(enemy.point.X), this.scaleSize(enemy.point.Y));
				var size = new Size(this.scaleSize(this._map.TileSize.Width), this.scaleSize(this._map.TileSize.Height));

				point.X -= (int)(size.Width / 2.0f);
				point.Y -= size.Height;
				e.Graphics.DrawImage(icon, new Rectangle(point, size));

				point.Y -= 20;
				e.Graphics.DrawString(enemy.name, SystemFonts.DefaultFont, Brushes.Black, point);
			}
		}

		private void mapTileListView_SelectedIndexChanged(object sender, EventArgs e)
		{
			var selectedItems = this.mapTileListView.SelectedItems;
			if (selectedItems.Count == 0)
				return;

			var selectedName = selectedItems[0].Text;
			using (var stream = new MemoryStream(this._map.Sprite[selectedName].Bytes))
			{
				this._currentIcon = Image.FromStream(stream);
				this._currentTileKey = selectedName;
			}

			this._action = Action.MapTile;
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e)
		{
			try
			{
				if (this._filename == null)
				{
					var dialog = new SaveFileDialog();
					dialog.DefaultExt = "pbm";
					dialog.Filter = "PB Map file (*.pbm)|*.pbm";

					if (dialog.ShowDialog() != DialogResult.OK)
						return;

					this._filename = dialog.FileName;
				}
				this._map.save(this._filename, this.bgmName.Text);
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
				dialog.DefaultExt = "pbm";
				dialog.Filter = "PB Map file (*.pbm)|*.pbm";

				if (dialog.ShowDialog() != DialogResult.OK)
					return;

				this._map.save(dialog.FileName, this.bgmName.Text);
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

			var sprite = this.loadSprite(dialog.FileName);


			dialog.Filter = "PB Map file(*.pbm)|*.pbm";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			this._map = new Map(dialog.FileName, sprite);
			try
			{
				this.enemyListView.Clear();
				foreach (var enemy in this._map.Enemies)
				{
					if (this.enemyListView.Items.ContainsKey(enemy.name))
						continue;

					this.enemyListView.Items.Add(enemy.name, enemy.name, 0);
				}
			}
			catch (Exception)
			{ }

			this._filename = dialog.FileName;
			this.bgmName.Text = this._map.BGMName;
			this._doubleBufferPanel.Invalidate();
			MessageBox.Show(this, "로드했음");
		}

		private void scaleTrackBar_Scroll(object sender, EventArgs e)
		{
			this._doubleBufferPanel.Invalidate();
		}

		private void newToolStripMenuItem_Click(object sender, EventArgs e)
		{
			var dialog = new MapAttrDialog();
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			var spriteDialog = new OpenFileDialog();
			spriteDialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
			if (spriteDialog.ShowDialog() != DialogResult.OK)
				return;

			this.initialize(dialog.Columns, dialog.Rows, dialog.TileWidth, dialog.TileHeight, spriteDialog.FileName);
		}

		private void canvasPanel_MouseDown(object sender, MouseEventArgs e)
		{
			try
			{
				switch (this._action)
				{
					case Action.MapTile:
						{
							var wIndex = e.X / this.scaleSize(this._map.TileSize.Width);
							var hIndex = e.Y / this.scaleSize(this._map.TileSize.Height);

							if (e.Button == MouseButtons.Left)
							{
								this._map[hIndex, wIndex] = new Map.Tile(Convert.ToByte(this._currentTileKey), this.Flags);
								this._isLButtonDown = true;
							}

							if (e.Button == MouseButtons.Right)
							{
								this._map[hIndex, wIndex] = null;
								this._isRButtonDown = true;
							}
						}
						break;

					case Action.RespawnPoint:
						{
							if (e.Button == MouseButtons.Left)
							{
								var adjustedPoint = this.AdjustedInGamePoint;
								adjustedPoint.X = (int)(adjustedPoint.X + this._map.TileSize.Width / 2.0f);
								adjustedPoint.Y = adjustedPoint.Y + this._map.TileSize.Height;

								this._map.RespawnPoints[this._currentRespawnPointIndex] = adjustedPoint;
							}
							else
							{
								for (var i = 0; i < this._map.RespawnPoints.Length; i++)
								{
									if (this._map.RespawnPoints[i] == null)
										continue;

									var x = (int)(this._map.RespawnPoints[i].Value.X - this._map.TileSize.Width / 2.0f);
									var y = this._map.RespawnPoints[i].Value.Y - this._map.TileSize.Height;
									var area = new Rectangle(new Point(x, y), this._map.TileSize);

									if (area.Contains(this.InGamePoint))
										this._map.RespawnPoints[i] = null;
								}
							}
						}
						break;

					case Action.Enemy:
						{
							if (e.Button == MouseButtons.Left)
							{
								var adjustedPoint = this.AdjustedInGamePoint;
								adjustedPoint.X = (int)(adjustedPoint.X + this._map.TileSize.Width / 2.0f);
								adjustedPoint.Y = adjustedPoint.Y + this._map.TileSize.Height;

								this._map.Enemies.Add(new Map.Enemy(this._currentEnemyName, adjustedPoint));
							}
							else
							{
								var deleted = null as Map.Enemy;
								foreach (var enemy in this._map.Enemies)
								{
									var x = (int)(enemy.point.X - this._map.TileSize.Width / 2.0f);
									var y = enemy.point.Y - this._map.TileSize.Height;
									var area = new Rectangle(new Point(x, y), this._map.TileSize);

									if (area.Contains(this.InGamePoint))
									{
										deleted = enemy;
										break;
									}
								}

								if (deleted != null)
									this._map.Enemies.Remove(deleted);
							}
						}
						break;
				}

				this._doubleBufferPanel.Invalidate();
			}
			catch (Exception)
			{

			}
		}

		private void canvasPanel_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
				this._isLButtonDown = false;

			if (e.Button == MouseButtons.Right)
				this._isRButtonDown = false;
		}

		private void respawnPointListView_SelectedIndexChanged(object sender, EventArgs e)
		{
			var selectedItem = this.respawnPointListView.SelectedItems.Count != 0 ? this.respawnPointListView.SelectedItems[0] : null;
			if (selectedItem == null)
				return;

			this._currentRespawnPointIndex = selectedItem.ImageIndex;
			this._currentIcon = selectedItem.ImageList.Images[this._currentRespawnPointIndex];
			this._action = Action.RespawnPoint;
		}

		private void respawnPointListView_Click(object sender, EventArgs e)
		{
			this._action = Action.RespawnPoint;
		}

		private void mapTileListView_Click(object sender, EventArgs e)
		{
			this._action = Action.MapTile;
		}

		private void buttonAddEnemy_Click(object sender, EventArgs e)
		{
			try
			{
				var enemyName = this.enemyNameTextBox.Text;
				if (enemyName == string.Empty)
					throw new Exception("이름을 입력해주세요.");

				foreach (ListViewItem item in this.enemyListView.Items)
				{
					if (item.Text.Equals(enemyName))
						throw new Exception("이미 존재하는 이름입니다.");
				}

				this.enemyListView.Items.Add(enemyName, enemyName, 0);
			}
			catch (Exception exc)
			{
				MessageBox.Show(exc.Message);
			}
		}

		private void enemyListView_SelectedIndexChanged(object sender, EventArgs e)
		{
			var selectedItem = this.enemyListView.SelectedItems.Count != 0 ? this.enemyListView.SelectedItems[0] : null;
			if (selectedItem == null)
				return;

			this._currentIcon = selectedItem.ImageList.Images[selectedItem.ImageIndex];
			this._currentEnemyName = selectedItem.Text;
			this._action = Action.Enemy;
		}

		private void canvasPanel_MouseMove(object sender, MouseEventArgs e)
		{
			try
			{
				this.CurrentPoint = e.Location;
				var wIndex = e.X / this.scaleSize(this._map.TileSize.Width);
				var hIndex = e.Y / this.scaleSize(this._map.TileSize.Height);


				if (this._isLButtonDown)
					this._map[hIndex, wIndex] = new Map.Tile(byte.Parse(this._currentTileKey), this.Flags);

				if (this._isRButtonDown)
					this._map[hIndex, wIndex] = null;

				this._doubleBufferPanel.Invalidate();
			}
			catch (Exception)
			{

			}
		}
	}
}