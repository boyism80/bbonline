using SpriteEditor;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace AnimationEditor
{
	public partial class MainForm : Form
    {
        private Animation _animation;
        private string _filename;

        public MainForm()
        {
            InitializeComponent();
        }

        private void updateAnimateActionsView()
        {
            this.animateActionsTreeView.Nodes.Clear();

            foreach(var pair in this._animation.animateActions)
            {
                var actionName = pair.Key;
                var action = pair.Value;

                var actionNode = this.animateActionsTreeView.Nodes.Add(actionName);
                actionNode.Tag = action;
                foreach(var frame in action.animateFrames)
                {
                    var frameNode = actionNode.Nodes.Add(frame.name);
                    frameNode.Tag = frame;
                }
            }
        }

        private void createToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                var dialog = new AddAnimationDialog(this._animation);
                if(dialog.ShowDialog() != DialogResult.OK)
                    return;

                var eachDuration = dialog.duration / (float)dialog.checkedSpriteNames.Length;
                var animateAction = new AnimateAction(dialog.name, dialog.isLoop);
                foreach(var spriteName in dialog.checkedSpriteNames)
                {
                    var animateFrame = new AnimateFrame(spriteName, new Point(), eachDuration);
                    animateAction.animateFrames.Add(animateFrame);
                }

                this._animation.animateActions.Add(dialog.name, animateAction);
                this.updateAnimateActionsView();
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void updateAnimationFrame()
        {
            var currentFrame = this._animation.currentAction.currentFrame;
            this.animateTimer.Interval = (int)(currentFrame.duration * 1000);
            this.animateTimer.Start();

            using (var stream = new MemoryStream(this._animation.Sprite[currentFrame.name].Bytes))
            {
                this.animateFrameBox.Image = Image.FromStream(stream);
            }
        }

        private void animateActionsTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            var animateAction = this.animateActionsTreeView.SelectedNode.Tag as AnimateAction;

            if(animateAction != null)
            {
                this.animateTimer.Stop();
                this._animation.change(animateAction.name);
                this.updateAnimationFrame();

                this.actionNameTextBox.Text         = animateAction.name;
                this.isLoopCheckBox.Checked         = animateAction.isLoop;
                this.durationTextBox.Text           = animateAction.duration.ToString();
            }
            else
            { }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog();
			dialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			var sprite = new Sprite(dialog.FileName);


			dialog.Filter = "PB Animation file(*.pba)|*.pba";
            if(dialog.ShowDialog() != DialogResult.OK)
                return;

			this._animation = new Animation(dialog.FileName, sprite);
            this._filename = dialog.FileName;
            this.updateAnimateActionsView();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if(this._animation == null || this._animation.animateActions.Count == 0)
                    throw new Exception("애니메이션이 없습니다.");

                if(this._filename == null)
                {
                    var dialog = new SaveFileDialog();
                    dialog.DefaultExt = "pba";
                    dialog.Filter = "PB Animation file (*.pba)|*.pba";

                    if(dialog.ShowDialog() != DialogResult.OK)
                        return;

                    this._filename = dialog.FileName;
                }

				this._animation.save(this._filename);
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                if(this._animation == null || this._animation.animateActions.Count == 0)
                    throw new Exception("애니메이션이 없습니다.");

                var dialog              = new SaveFileDialog();
                dialog.FileName         = Path.GetFileName(this._filename);
                dialog.DefaultExt = "pba";
                    dialog.Filter = "PB Animation file (*.pba)|*.pba";

                if(dialog.ShowDialog() != DialogResult.OK)
                    return;

				this._animation.save(dialog.FileName);
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void animateTimer_Tick(object sender, EventArgs e)
        {
			try
			{
				if (this._animation.currentAction.next() == false)
				{
					this.animateTimer.Enabled = false;
					return;
				}

				this.updateAnimationFrame();
			}
			catch (Exception)
			{ }
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.animateTimer.Stop();
            this.animateFrameBox.Image = null;
            this.animateActionsTreeView.Nodes.Clear();

            this._filename = null;
            this._animation = null;

			var dialog = new OpenFileDialog();
			dialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			this._animation = new Animation(new Sprite(dialog.FileName));
		}

        private void applyButton_Click(object sender, EventArgs e)
        {
            var animateAction                   = this._animation.currentAction;
            if(animateAction == null)
                return;

            try
            {
                var prevName                    = animateAction.name;

                animateAction.name              = this.actionNameTextBox.Text;
                animateAction.isLoop            = this.isLoopCheckBox.Checked;
                animateAction.duration          = float.Parse(this.durationTextBox.Text);

                this._animation.animateActions.Remove(prevName);
                this._animation.animateActions.Add(animateAction.name, animateAction);
                this.updateAnimateActionsView();
                this.restartButton_Click(this.restartButton, EventArgs.Empty);
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message);
            }
        }

        private void restartButton_Click(object sender, EventArgs e)
        {
            this._animation.reset();
            this.updateAnimationFrame();
        }

		private void MainForm_Load(object sender, EventArgs e)
		{
			var dialog = new OpenFileDialog();
			dialog.Filter = "PB Sprite files(*.pbs)|*.pbs";
			if (dialog.ShowDialog() != DialogResult.OK)
				return;

			this._animation = new Animation(new Sprite(dialog.FileName));
		}
	}
}