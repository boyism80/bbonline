using OpenCvSharp;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace SpriteEditor
{
	public partial class PBSpriteManager : Form
    {
        private string _filename = null;
		private Sprite _sprite = new Sprite();

        public PBSpriteManager()
        {
            InitializeComponent();

			this.pivots.SelectedIndex = (int)Sprite.Pivot.CenterBottom;

			this.spriteSheetPanel.GridSizeChanged += this.SpriteSheetPanel_GridSizeChanged;
			this.spriteSheetPanel.ScaleChanged += this.SpriteSheetPanel_ScaleChanged;
        }

		private void SpriteSheetPanel_ScaleChanged(object sender, float scale)
		{
			this.zoomScale.Text = scale.ToString();
		}

		private void SpriteSheetPanel_GridSizeChanged(object sender, Rectangle area)
		{
			this.gridX.Text = area.X.ToString();
			this.gridY.Text = area.Y.ToString();
			this.gridWidth.Text = area.Width.ToString();
			this.gridHeight.Text = area.Height.ToString();
		}

		private void updateGridView()
        {
			var selectedIndex = this.spriteGridView.CurrentCell != null ? this.spriteGridView.CurrentCell.RowIndex : -1;
            this.spriteGridView.Rows.Clear();
            foreach(var pair in this._sprite)
            {
                var row                 = new DataGridViewRow();
                row.CreateCells(this.spriteGridView, pair.Key);
                row.Tag                 = pair.Key;
                this.spriteGridView.Rows.Add(row);
            }

			if (selectedIndex != -1)
			{
				foreach (DataGridViewRow selectedRow in this.spriteGridView.SelectedRows)
					selectedRow.Selected = false;

				if(this.spriteGridView.Rows.Count != 0)
					this.spriteGridView.Rows[selectedIndex].Selected = true;
			}
        }

        private void loadSpriteButton_Click(object sender, EventArgs e)
        {
            var dialog          = new OpenFileDialog();
            dialog.Multiselect  = true;
            dialog.Filter       = "Image files|*.jpg;*.jpeg;*.png;";
            if(dialog.ShowDialog() != DialogResult.OK)
                return;

            var fileNames       = dialog.FileNames;
            foreach(var path in fileNames)
				this._sprite.add(path, Sprite.Pivot.CenterBottom);

            this.updateGridView();
        }

        private void spriteGridView_SelectionChanged(object sender, EventArgs e)
        {
            this.canvasPanel.Controls.Clear();

            var selections       = this.spriteGridView.SelectedRows;
            if(selections.Count == 0)
                return;

            var selected        = selections[0];
            var name            = selected.Tag as string;
            var spriteElement   = this._sprite[name];

            using (var stream = new MemoryStream(spriteElement.Bytes))
            {
                // Add picture box
                var pictureBox      = new PictureBox();
                pictureBox.Image    = Image.FromStream(stream);
                pictureBox.SizeMode = PictureBoxSizeMode.AutoSize;
                pictureBox.Name     = name;
                this.canvasPanel.Controls.Add(pictureBox);

                // Set image information
                this.spriteNameTextBox.Text         = name;
                this.spriteSizeTextBox.Text         = string.Format("{0} * {1}", pictureBox.Width, pictureBox.Height);
            }

			this.pivots.SelectedIndex = (int)spriteElement.Pivot;
		}

        private void applyButton_Click(object sender, EventArgs e)
        {
            try
            {
                var selections      = this.spriteGridView.SelectedRows;
                if(selections.Count == 0)
                    throw new Exception("선택하세요");

                var selected        = selections[0];
                var src				= selected.Tag as string;
                var dest			= this.spriteNameTextBox.Text;

				var spriteElement = this._sprite[src];
				spriteElement.Pivot = (Sprite.Pivot)this.pivots.SelectedIndex;
				this._sprite.rename(src, dest);
				
				this.updateGridView();
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
			this._sprite.clear();
            this._filename                  = null;
            this.spriteNameTextBox.Text     = string.Empty;
            this.spriteSizeTextBox.Text     = string.Empty;
            this.updateGridView();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dialog              = new OpenFileDialog();
            dialog.Filter           = "PB Sprite files(*.pbs)|*.pbs";

            if(dialog.ShowDialog() != DialogResult.OK)
                return;

            try
            {
                if(File.Exists(dialog.FileName) == false)
                    throw new FileNotFoundException();

				this._sprite.load(dialog.FileName);
                this._filename      = dialog.FileName;
				this.updateGridView();
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(this._filename == null)
            {
                var dialog              = new SaveFileDialog();
                dialog.DefaultExt       = "pbs";
                dialog.Filter           = "PB Sprite file (*.pbs)|*.pbs";

                if(dialog.ShowDialog() != DialogResult.OK)
                    return;

                this._filename          = dialog.FileName;
            }

			this._sprite.save(this._filename);
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dialog              = new SaveFileDialog();
            dialog.DefaultExt       = "pbs";
            dialog.FileName         = Path.GetFileName(this._filename);
            dialog.Filter           = "PB Sprite file (*.pbs)|*.pbs";

            if(dialog.ShowDialog() != DialogResult.OK)
                return;

			this._sprite.save(dialog.FileName);
        }

		private void buttonLoadSpriteSheet_Click(object sender, EventArgs e)
		{
			var dialog = new OpenFileDialog();
			dialog.Filter = "Image files|*.jpg;*.jpeg;*.png;";
			if (dialog.ShowDialog(this) != DialogResult.OK)
				return;

			this.spriteSheetPanel.Source = Cv2.ImRead(dialog.FileName, ImreadModes.Unchanged);
		}

		private void drawGrid_CheckedChanged(object sender, EventArgs e)
		{
			this.spriteSheetPanel.DrawGrid = this.drawGrid.Checked;
			this.gridRows_TextChanged(this.gridRows, EventArgs.Empty);
			this.gridColumns_TextChanged(this.gridColumns, EventArgs.Empty);
		}

		private void textBox1_TextChanged(object sender, EventArgs e)
		{

		}

		private void gridRows_TextChanged(object sender, EventArgs e)
		{
			try
			{
				this.spriteSheetPanel.Rows = int.Parse(this.gridRows.Text);
			}
			catch (Exception)
			{ }
		}

		private void gridColumns_TextChanged(object sender, EventArgs e)
		{
			try
			{
				this.spriteSheetPanel.Columns = int.Parse(this.gridColumns.Text);
			}
			catch (Exception)
			{ }
		}

		private void buttonSave_Click(object sender, EventArgs e)
		{
			var dialog = new SaveFileDialog();
			dialog.Filter = "Image files|*.png";
			if (dialog.ShowDialog(this) != DialogResult.OK)
				return;

			if (this.spriteSheetPanel.save(dialog.FileName) == false)
				MessageBox.Show("파일을 저장할 수 없습니다.");
		}

		private void zoomScale_TextChanged(object sender, EventArgs e)
		{
			try
			{
				this.spriteSheetPanel.Scale = float.Parse(this.zoomScale.Text);
			}
			catch (Exception)
			{ }
		}
	}
}