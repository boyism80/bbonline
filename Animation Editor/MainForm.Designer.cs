namespace AnimationEditor
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.components = new System.ComponentModel.Container();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.createToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.animateActionsTreeView = new System.Windows.Forms.TreeView();
			this.splitContainer2 = new System.Windows.Forms.SplitContainer();
			this.canvasPanel = new System.Windows.Forms.Panel();
			this.animateFrameBox = new System.Windows.Forms.PictureBox();
			this.panel10 = new System.Windows.Forms.Panel();
			this.restartButton = new System.Windows.Forms.Button();
			this.applyButton = new System.Windows.Forms.Button();
			this.panel7 = new System.Windows.Forms.Panel();
			this.panel8 = new System.Windows.Forms.Panel();
			this.durationTextBox = new System.Windows.Forms.TextBox();
			this.panel9 = new System.Windows.Forms.Panel();
			this.label3 = new System.Windows.Forms.Label();
			this.panel4 = new System.Windows.Forms.Panel();
			this.panel5 = new System.Windows.Forms.Panel();
			this.isLoopCheckBox = new System.Windows.Forms.CheckBox();
			this.panel6 = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel3 = new System.Windows.Forms.Panel();
			this.actionNameTextBox = new System.Windows.Forms.TextBox();
			this.panel2 = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.animateTimer = new System.Windows.Forms.Timer(this.components);
			this.menuStrip1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
			this.splitContainer2.Panel1.SuspendLayout();
			this.splitContainer2.Panel2.SuspendLayout();
			this.splitContainer2.SuspendLayout();
			this.canvasPanel.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.animateFrameBox)).BeginInit();
			this.panel10.SuspendLayout();
			this.panel7.SuspendLayout();
			this.panel8.SuspendLayout();
			this.panel9.SuspendLayout();
			this.panel4.SuspendLayout();
			this.panel5.SuspendLayout();
			this.panel6.SuspendLayout();
			this.panel1.SuspendLayout();
			this.panel3.SuspendLayout();
			this.panel2.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(906, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// newToolStripMenuItem
			// 
			this.newToolStripMenuItem.Name = "newToolStripMenuItem";
			this.newToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.newToolStripMenuItem.Text = "New";
			this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
			this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.saveAsToolStripMenuItem.Text = "Save as";
			this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.createToolStripMenuItem});
			this.editToolStripMenuItem.Name = "editToolStripMenuItem";
			this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
			this.editToolStripMenuItem.Text = "Edit";
			// 
			// createToolStripMenuItem
			// 
			this.createToolStripMenuItem.Name = "createToolStripMenuItem";
			this.createToolStripMenuItem.Size = new System.Drawing.Size(108, 22);
			this.createToolStripMenuItem.Text = "Create";
			this.createToolStripMenuItem.Click += new System.EventHandler(this.createToolStripMenuItem_Click);
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 24);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.animateActionsTreeView);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
			this.splitContainer1.Size = new System.Drawing.Size(906, 570);
			this.splitContainer1.SplitterDistance = 201;
			this.splitContainer1.TabIndex = 1;
			// 
			// animateActionsTreeView
			// 
			this.animateActionsTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.animateActionsTreeView.Location = new System.Drawing.Point(0, 0);
			this.animateActionsTreeView.Name = "animateActionsTreeView";
			this.animateActionsTreeView.Size = new System.Drawing.Size(201, 570);
			this.animateActionsTreeView.TabIndex = 0;
			this.animateActionsTreeView.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.animateActionsTreeView_AfterSelect);
			// 
			// splitContainer2
			// 
			this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer2.Location = new System.Drawing.Point(0, 0);
			this.splitContainer2.Name = "splitContainer2";
			this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this.splitContainer2.Panel1.Controls.Add(this.canvasPanel);
			// 
			// splitContainer2.Panel2
			// 
			this.splitContainer2.Panel2.Controls.Add(this.panel10);
			this.splitContainer2.Panel2.Controls.Add(this.panel7);
			this.splitContainer2.Panel2.Controls.Add(this.panel4);
			this.splitContainer2.Panel2.Controls.Add(this.panel1);
			this.splitContainer2.Size = new System.Drawing.Size(701, 570);
			this.splitContainer2.SplitterDistance = 435;
			this.splitContainer2.TabIndex = 0;
			// 
			// canvasPanel
			// 
			this.canvasPanel.Controls.Add(this.animateFrameBox);
			this.canvasPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.canvasPanel.Location = new System.Drawing.Point(0, 0);
			this.canvasPanel.Name = "canvasPanel";
			this.canvasPanel.Size = new System.Drawing.Size(701, 435);
			this.canvasPanel.TabIndex = 0;
			// 
			// animateFrameBox
			// 
			this.animateFrameBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.animateFrameBox.Location = new System.Drawing.Point(0, 0);
			this.animateFrameBox.Name = "animateFrameBox";
			this.animateFrameBox.Size = new System.Drawing.Size(701, 435);
			this.animateFrameBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
			this.animateFrameBox.TabIndex = 0;
			this.animateFrameBox.TabStop = false;
			// 
			// panel10
			// 
			this.panel10.Controls.Add(this.restartButton);
			this.panel10.Controls.Add(this.applyButton);
			this.panel10.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel10.Location = new System.Drawing.Point(0, 93);
			this.panel10.Name = "panel10";
			this.panel10.Padding = new System.Windows.Forms.Padding(5);
			this.panel10.Size = new System.Drawing.Size(701, 38);
			this.panel10.TabIndex = 2;
			// 
			// restartButton
			// 
			this.restartButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.restartButton.Location = new System.Drawing.Point(546, 5);
			this.restartButton.Name = "restartButton";
			this.restartButton.Size = new System.Drawing.Size(75, 28);
			this.restartButton.TabIndex = 1;
			this.restartButton.Text = "Restart";
			this.restartButton.UseVisualStyleBackColor = true;
			this.restartButton.Click += new System.EventHandler(this.restartButton_Click);
			// 
			// applyButton
			// 
			this.applyButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.applyButton.Location = new System.Drawing.Point(621, 5);
			this.applyButton.Name = "applyButton";
			this.applyButton.Size = new System.Drawing.Size(75, 28);
			this.applyButton.TabIndex = 0;
			this.applyButton.Text = "Apply";
			this.applyButton.UseVisualStyleBackColor = true;
			this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
			// 
			// panel7
			// 
			this.panel7.Controls.Add(this.panel8);
			this.panel7.Controls.Add(this.panel9);
			this.panel7.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel7.Location = new System.Drawing.Point(0, 62);
			this.panel7.Name = "panel7";
			this.panel7.Size = new System.Drawing.Size(701, 31);
			this.panel7.TabIndex = 2;
			// 
			// panel8
			// 
			this.panel8.Controls.Add(this.durationTextBox);
			this.panel8.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel8.Location = new System.Drawing.Point(70, 0);
			this.panel8.Name = "panel8";
			this.panel8.Padding = new System.Windows.Forms.Padding(3);
			this.panel8.Size = new System.Drawing.Size(631, 31);
			this.panel8.TabIndex = 1;
			// 
			// durationTextBox
			// 
			this.durationTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.durationTextBox.Location = new System.Drawing.Point(3, 3);
			this.durationTextBox.Name = "durationTextBox";
			this.durationTextBox.Size = new System.Drawing.Size(625, 21);
			this.durationTextBox.TabIndex = 0;
			// 
			// panel9
			// 
			this.panel9.Controls.Add(this.label3);
			this.panel9.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel9.Location = new System.Drawing.Point(0, 0);
			this.panel9.Name = "panel9";
			this.panel9.Padding = new System.Windows.Forms.Padding(3);
			this.panel9.Size = new System.Drawing.Size(70, 31);
			this.panel9.TabIndex = 0;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(6, 12);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(51, 12);
			this.label3.TabIndex = 0;
			this.label3.Text = "Duration";
			// 
			// panel4
			// 
			this.panel4.Controls.Add(this.panel5);
			this.panel4.Controls.Add(this.panel6);
			this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel4.Location = new System.Drawing.Point(0, 31);
			this.panel4.Name = "panel4";
			this.panel4.Size = new System.Drawing.Size(701, 31);
			this.panel4.TabIndex = 1;
			// 
			// panel5
			// 
			this.panel5.Controls.Add(this.isLoopCheckBox);
			this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel5.Location = new System.Drawing.Point(70, 0);
			this.panel5.Name = "panel5";
			this.panel5.Padding = new System.Windows.Forms.Padding(3);
			this.panel5.Size = new System.Drawing.Size(631, 31);
			this.panel5.TabIndex = 1;
			// 
			// isLoopCheckBox
			// 
			this.isLoopCheckBox.AutoSize = true;
			this.isLoopCheckBox.Location = new System.Drawing.Point(6, 6);
			this.isLoopCheckBox.Name = "isLoopCheckBox";
			this.isLoopCheckBox.Size = new System.Drawing.Size(62, 16);
			this.isLoopCheckBox.TabIndex = 0;
			this.isLoopCheckBox.Text = "isLoop";
			this.isLoopCheckBox.UseVisualStyleBackColor = true;
			// 
			// panel6
			// 
			this.panel6.Controls.Add(this.label2);
			this.panel6.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel6.Location = new System.Drawing.Point(0, 0);
			this.panel6.Name = "panel6";
			this.panel6.Padding = new System.Windows.Forms.Padding(3);
			this.panel6.Size = new System.Drawing.Size(70, 31);
			this.panel6.TabIndex = 0;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 12);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(57, 12);
			this.label2.TabIndex = 0;
			this.label2.Text = "Attributes";
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.panel3);
			this.panel1.Controls.Add(this.panel2);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(701, 31);
			this.panel1.TabIndex = 0;
			// 
			// panel3
			// 
			this.panel3.Controls.Add(this.actionNameTextBox);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel3.Location = new System.Drawing.Point(70, 0);
			this.panel3.Name = "panel3";
			this.panel3.Padding = new System.Windows.Forms.Padding(3);
			this.panel3.Size = new System.Drawing.Size(631, 31);
			this.panel3.TabIndex = 1;
			// 
			// actionNameTextBox
			// 
			this.actionNameTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.actionNameTextBox.Location = new System.Drawing.Point(3, 3);
			this.actionNameTextBox.Name = "actionNameTextBox";
			this.actionNameTextBox.Size = new System.Drawing.Size(625, 21);
			this.actionNameTextBox.TabIndex = 0;
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.label1);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel2.Location = new System.Drawing.Point(0, 0);
			this.panel2.Name = "panel2";
			this.panel2.Padding = new System.Windows.Forms.Padding(3);
			this.panel2.Size = new System.Drawing.Size(70, 31);
			this.panel2.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(39, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "Name";
			// 
			// animateTimer
			// 
			this.animateTimer.Tick += new System.EventHandler(this.animateTimer_Tick);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(906, 594);
			this.Controls.Add(this.splitContainer1);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "MainForm";
			this.Text = "PBAnimation manager";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.splitContainer2.Panel1.ResumeLayout(false);
			this.splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
			this.splitContainer2.ResumeLayout(false);
			this.canvasPanel.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.animateFrameBox)).EndInit();
			this.panel10.ResumeLayout(false);
			this.panel7.ResumeLayout(false);
			this.panel8.ResumeLayout(false);
			this.panel8.PerformLayout();
			this.panel9.ResumeLayout(false);
			this.panel9.PerformLayout();
			this.panel4.ResumeLayout(false);
			this.panel5.ResumeLayout(false);
			this.panel5.PerformLayout();
			this.panel6.ResumeLayout(false);
			this.panel6.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem createToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TreeView animateActionsTreeView;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Panel canvasPanel;
        private System.Windows.Forms.Timer animateTimer;
        private System.Windows.Forms.PictureBox animateFrameBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.TextBox actionNameTextBox;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.TextBox durationTextBox;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox isLoopCheckBox;
        private System.Windows.Forms.Panel panel10;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.Button restartButton;
    }
}

