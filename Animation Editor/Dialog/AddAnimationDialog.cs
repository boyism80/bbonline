using SpriteEditor;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace AnimationEditor
{
	public partial class AddAnimationDialog : Form
    {
		private Sprite _sprite;

        public string name { get; private set; }
        public string[] checkedSpriteNames { get; private set; }
        public bool isLoop { get; private set; }
        public float duration { get; private set; }

        public AddAnimationDialog(Animation animation)
        {
            InitializeComponent();

            if(animation == null || animation.Sprite == null || animation.Sprite.Count == 0)
                throw new Exception("sprite가 선택되지 않았습니다.");

            this._sprite = animation.Sprite;

            foreach (var pair in animation.Sprite)
                this.spriteListBox.Items.Add(pair.Key);
        }

        private void createButton_Click(object sender, EventArgs e)
        {
            try
            {
                if(this.spriteListBox.CheckedItems.Count == 0)
                    throw new Exception("이미지를 하나 이상 설정하세요.");

                if(this.nameTextBox.Text.Length == 0)
                    throw new Exception("이름을 입력하세요.");

                if(this.durationTextBox.Text.Length == 0)
                    throw new Exception("지속시간을 입력하세요.");

                this.duration = float.Parse(this.durationTextBox.Text);
                this.name = this.nameTextBox.Text;
                this.isLoop = this.loopCheckBox.Checked;
                this.checkedSpriteNames = new string[this.spriteListBox.CheckedItems.Count];
                for(var i = 0; i < this.spriteListBox.CheckedItems.Count; i++)
                    this.checkedSpriteNames[i] = this.spriteListBox.CheckedItems[i] as string;


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
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void spriteListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedName = this.spriteListBox.SelectedItem as string;
            if(selectedName == null)
                return;

            using (var stream = new MemoryStream(this._sprite[selectedName].Bytes))
            {
                this.spriteImageBox.Image = Image.FromStream(stream);
            }
        }
    }
}