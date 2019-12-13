using System;
using System.Windows.Forms;

namespace MapEditor
{
	public partial class MapAttrDialog : Form
	{
		public int TileWidth
		{
			get
			{
				return int.Parse(this.tileWidthTextBox.Text);
			}
			private set
			{
				this.tileWidthTextBox.Text = value.ToString();
			}
		}

		public int TileHeight
		{
			get
			{
				return int.Parse(this.tileHeightTextBox.Text);
			}
			private set
			{
				this.tileHeightTextBox.Text = value.ToString();
			}
		}

		public int Columns
		{
			get
			{
				return int.Parse(this.columnsTextBox.Text);
			}
			private set
			{
				this.columnsTextBox.Text = value.ToString();
			}
		}

		public int Rows
		{
			get
			{
				return int.Parse(this.rowsTextBox.Text);
			}
			private set
			{
				this.rowsTextBox.Text = value.ToString();
			}
		}

		public MapAttrDialog()
		{
			InitializeComponent();
		}

		private void OKButton_Click(object sender, EventArgs e)
		{
			try
			{
				var tileWidth = this.TileWidth;
				var tileHeight = this.TileHeight;
				var rows = this.Columns;
				var cols = this.Rows;

				this.DialogResult = DialogResult.OK;
				this.Close();
			}
			catch (Exception exc)
			{
				MessageBox.Show(this, exc.Message);
			}
		}

		private void cancelButton_Click(object sender, EventArgs e)
		{
			this.Close();
		}
	}
}