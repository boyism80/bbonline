using System;
using System.Windows.Forms;

namespace WindowEditor
{
    public partial class MainWindowAttrDialog : Form
    {

        public int WindowWidth
        {
            get
            {
                return int.Parse(this.MainWindowWidthTextBox.Text);
            }
            private set
            {
                this.MainWindowWidthTextBox.Text = value.ToString();
            }
        }

        public int WindowHeight
        {
            get
            {
                return int.Parse(this.MainWindowHeightTextBox.Text);
            }
            private set
            {
                this.MainWindowHeightTextBox.Text = value.ToString();
            }
        }

        public MainWindowAttrDialog()
        {
            InitializeComponent();
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            try
            {
                var WindowWidth = this.WindowWidth;
                var WindowHeight = this.WindowHeight;

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
