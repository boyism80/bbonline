using System;
using System.Windows.Forms;

namespace WindowEditor
{
    public partial class SubWindowAttrDialog : Form
    {
        public int WindowX
        {
            get
            {
                return int.Parse(this.SubWindowXTextBox.Text);
            }
            set
            {
                this.SubWindowXTextBox.Text = value.ToString();
            }
        }

        public int WindowY
        {
            get
            {
                return int.Parse(this.SubWindowYTextBox.Text);
            }
            set
            {
                this.SubWindowYTextBox.Text = value.ToString();
            }
        }

        public int WindowWidth
        {
            get
            {
                return int.Parse(this.SubWindowWidthTextBox.Text);
            }
            set
            {
                this.SubWindowWidthTextBox.Text = value.ToString();
            }
        }

        public int WindowHeight
        {
            get
            {
                return int.Parse(this.SubWindowHeightTextBox.Text);
            }
            set
            {
                this.SubWindowHeightTextBox.Text = value.ToString();
            }
        }

        public String WindowId
        {
            get
            {
                return this.SubWindowIdTextBox.Text;
            }
            set
            {
                this.SubWindowIdTextBox.Text = value.ToString();
            }
        }

        public String WindowText
        {
            get
            {
                return this.SubWindowTextTextBox.Text;
            }
            set
            {
                this.SubWindowTextTextBox.Text = value.ToString();
            }
        }

        public String WindowPurpose
        {
            get
            {
                return this.SubWindowPurposeComboBox.Items[SubWindowPurposeComboBox.SelectedIndex].ToString();
            }
            set
            {
                this.SubWindowPurposeComboBox.Text = value;
            }
        }

        public bool WindowUseImage
        {
            get
            {
                return this.UseImageCheckBox.Checked;
            }
            set
            {
                this.UseImageCheckBox.Checked = value;
            }
        }

        public bool WindowInvisible
        {
            get
            {
                return this.InvisibleCheckBox.Checked;
            }
            set
            {
                this.InvisibleCheckBox.Checked = value;
            }
        }

        public SubWindowAttrDialog()
        {
            InitializeComponent();

            SubWindowPurposeComboBox.SelectedIndex = 0;
        }
        public SubWindowAttrDialog(Window win) : this()
        {
            
            this.WindowX = win.Location.X;
            this.WindowY = win.Location.Y;
            this.WindowWidth = win.Size.Width;
            this.WindowHeight = win.Size.Height;
            this.WindowId = win.Id;
            this.WindowText = win.Text;
            this.WindowPurpose = win.Purpose;
            this.WindowUseImage = win.SpriteName != "";
            this.WindowInvisible = win.isVisible;

            if (win.Parent == null)
            {
                this.SubWindowIdTextBox.ReadOnly = true;
                this.SubWindowPurposeComboBox.Enabled = false;
                this.SubWindowTextTextBox.ReadOnly = true;
                this.SubWindowXTextBox.ReadOnly = true;
                this.SubWindowYTextBox.ReadOnly = true;
                this.UseImageCheckBox.Enabled = false;
            }

        }
        private void OKButton_Click(object sender, EventArgs e)
        {
            try
            {
                var WindowX = this.WindowX;
                var WindowY = this.WindowY;
                var WindowWidth = this.WindowWidth;
                var WindowHeight = this.WindowHeight;
                var WindowId = this.WindowId;
                var WindowPurpose = this.WindowPurpose;
                var WindowText = this.WindowText;
                var WindowUseImage = this.WindowUseImage;
                var WindowInvisible = this.WindowInvisible;


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

        private void SubWindowPurposeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (WindowPurpose.Equals("Label"))
            {
                WindowUseImage = false;
                this.UseImageCheckBox.Enabled = false;
            }
            else
            {
                this.UseImageCheckBox.Enabled = true;
            }
        }
    }
}
