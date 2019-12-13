using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PBMapManager
{
    public partial class MapAttrDialoog : Form
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

        public int Cols
        {
            get
            {
                return int.Parse(this.colsTextBox.Text);
            }
            private set
            {
                this.colsTextBox.Text = value.ToString();
            }
        }

        public MapAttrDialoog()
        {
            InitializeComponent();
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            try
            {
                var tileWidth = this.TileWidth;
                var tileHeight = this.TileHeight;
                var rows = this.Rows;
                var cols = this.Cols;

                this.DialogResult = DialogResult.OK;
                this.Close();
            }
            catch(Exception exc)
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