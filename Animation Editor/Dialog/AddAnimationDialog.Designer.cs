namespace AnimationEditor
{
    partial class AddAnimationDialog
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
			this.panel1 = new System.Windows.Forms.Panel();
			this.createButton = new System.Windows.Forms.Button();
			this.cancelButton = new System.Windows.Forms.Button();
			this.panel2 = new System.Windows.Forms.Panel();
			this.panel10 = new System.Windows.Forms.Panel();
			this.panel11 = new System.Windows.Forms.Panel();
			this.durationTextBox = new System.Windows.Forms.TextBox();
			this.panel12 = new System.Windows.Forms.Panel();
			this.label3 = new System.Windows.Forms.Label();
			this.panel6 = new System.Windows.Forms.Panel();
			this.panel7 = new System.Windows.Forms.Panel();
			this.loopCheckBox = new System.Windows.Forms.CheckBox();
			this.panel8 = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.panel3 = new System.Windows.Forms.Panel();
			this.panel5 = new System.Windows.Forms.Panel();
			this.nameTextBox = new System.Windows.Forms.TextBox();
			this.panel4 = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.panel9 = new System.Windows.Forms.Panel();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.spriteListBox = new System.Windows.Forms.CheckedListBox();
			this.spriteImageBox = new System.Windows.Forms.PictureBox();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			this.panel10.SuspendLayout();
			this.panel11.SuspendLayout();
			this.panel12.SuspendLayout();
			this.panel6.SuspendLayout();
			this.panel7.SuspendLayout();
			this.panel8.SuspendLayout();
			this.panel3.SuspendLayout();
			this.panel5.SuspendLayout();
			this.panel4.SuspendLayout();
			this.panel9.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.spriteImageBox)).BeginInit();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.createButton);
			this.panel1.Controls.Add(this.cancelButton);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel1.Location = new System.Drawing.Point(0, 470);
			this.panel1.Name = "panel1";
			this.panel1.Padding = new System.Windows.Forms.Padding(0, 5, 5, 5);
			this.panel1.Size = new System.Drawing.Size(637, 36);
			this.panel1.TabIndex = 0;
			// 
			// createButton
			// 
			this.createButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.createButton.Location = new System.Drawing.Point(482, 5);
			this.createButton.Name = "createButton";
			this.createButton.Size = new System.Drawing.Size(75, 26);
			this.createButton.TabIndex = 2;
			this.createButton.Text = "Create";
			this.createButton.UseVisualStyleBackColor = true;
			this.createButton.Click += new System.EventHandler(this.createButton_Click);
			// 
			// cancelButton
			// 
			this.cancelButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.cancelButton.Location = new System.Drawing.Point(557, 5);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(75, 26);
			this.cancelButton.TabIndex = 1;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
			// 
			// panel2
			// 
			this.panel2.AutoSize = true;
			this.panel2.Controls.Add(this.panel10);
			this.panel2.Controls.Add(this.panel6);
			this.panel2.Controls.Add(this.panel3);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel2.Location = new System.Drawing.Point(0, 362);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(637, 108);
			this.panel2.TabIndex = 1;
			// 
			// panel10
			// 
			this.panel10.Controls.Add(this.panel11);
			this.panel10.Controls.Add(this.panel12);
			this.panel10.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel10.Location = new System.Drawing.Point(0, 72);
			this.panel10.Name = "panel10";
			this.panel10.Size = new System.Drawing.Size(637, 36);
			this.panel10.TabIndex = 2;
			// 
			// panel11
			// 
			this.panel11.AutoSize = true;
			this.panel11.Controls.Add(this.durationTextBox);
			this.panel11.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel11.Location = new System.Drawing.Point(85, 0);
			this.panel11.Name = "panel11";
			this.panel11.Padding = new System.Windows.Forms.Padding(7, 7, 7, 7);
			this.panel11.Size = new System.Drawing.Size(552, 36);
			this.panel11.TabIndex = 1;
			// 
			// durationTextBox
			// 
			this.durationTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.durationTextBox.Location = new System.Drawing.Point(7, 7);
			this.durationTextBox.Name = "durationTextBox";
			this.durationTextBox.Size = new System.Drawing.Size(538, 21);
			this.durationTextBox.TabIndex = 1;
			// 
			// panel12
			// 
			this.panel12.AutoScroll = true;
			this.panel12.Controls.Add(this.label3);
			this.panel12.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel12.Location = new System.Drawing.Point(0, 0);
			this.panel12.Name = "panel12";
			this.panel12.Size = new System.Drawing.Size(85, 36);
			this.panel12.TabIndex = 0;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(3, 11);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(51, 12);
			this.label3.TabIndex = 0;
			this.label3.Text = "Duration";
			// 
			// panel6
			// 
			this.panel6.Controls.Add(this.panel7);
			this.panel6.Controls.Add(this.panel8);
			this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel6.Location = new System.Drawing.Point(0, 36);
			this.panel6.Name = "panel6";
			this.panel6.Size = new System.Drawing.Size(637, 36);
			this.panel6.TabIndex = 1;
			// 
			// panel7
			// 
			this.panel7.AutoSize = true;
			this.panel7.Controls.Add(this.loopCheckBox);
			this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel7.Location = new System.Drawing.Point(85, 0);
			this.panel7.Name = "panel7";
			this.panel7.Padding = new System.Windows.Forms.Padding(7, 7, 7, 7);
			this.panel7.Size = new System.Drawing.Size(552, 36);
			this.panel7.TabIndex = 1;
			// 
			// loopCheckBox
			// 
			this.loopCheckBox.AutoSize = true;
			this.loopCheckBox.Location = new System.Drawing.Point(10, 11);
			this.loopCheckBox.Name = "loopCheckBox";
			this.loopCheckBox.Size = new System.Drawing.Size(52, 16);
			this.loopCheckBox.TabIndex = 0;
			this.loopCheckBox.Text = "Loop";
			this.loopCheckBox.UseVisualStyleBackColor = true;
			// 
			// panel8
			// 
			this.panel8.AutoScroll = true;
			this.panel8.Controls.Add(this.label2);
			this.panel8.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel8.Location = new System.Drawing.Point(0, 0);
			this.panel8.Name = "panel8";
			this.panel8.Size = new System.Drawing.Size(85, 36);
			this.panel8.TabIndex = 0;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(3, 11);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(50, 12);
			this.label2.TabIndex = 0;
			this.label2.Text = "Attribute";
			// 
			// panel3
			// 
			this.panel3.Controls.Add(this.panel5);
			this.panel3.Controls.Add(this.panel4);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel3.Location = new System.Drawing.Point(0, 0);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(637, 36);
			this.panel3.TabIndex = 0;
			// 
			// panel5
			// 
			this.panel5.AutoSize = true;
			this.panel5.Controls.Add(this.nameTextBox);
			this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel5.Location = new System.Drawing.Point(85, 0);
			this.panel5.Name = "panel5";
			this.panel5.Padding = new System.Windows.Forms.Padding(7, 7, 7, 7);
			this.panel5.Size = new System.Drawing.Size(552, 36);
			this.panel5.TabIndex = 1;
			// 
			// nameTextBox
			// 
			this.nameTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.nameTextBox.Location = new System.Drawing.Point(7, 7);
			this.nameTextBox.Name = "nameTextBox";
			this.nameTextBox.Size = new System.Drawing.Size(538, 21);
			this.nameTextBox.TabIndex = 0;
			// 
			// panel4
			// 
			this.panel4.AutoScroll = true;
			this.panel4.Controls.Add(this.label1);
			this.panel4.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel4.Location = new System.Drawing.Point(0, 0);
			this.panel4.Name = "panel4";
			this.panel4.Size = new System.Drawing.Size(85, 36);
			this.panel4.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(3, 11);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(39, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "Name";
			// 
			// panel9
			// 
			this.panel9.Controls.Add(this.splitContainer1);
			this.panel9.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel9.Location = new System.Drawing.Point(0, 0);
			this.panel9.Name = "panel9";
			this.panel9.Size = new System.Drawing.Size(637, 362);
			this.panel9.TabIndex = 2;
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.spriteListBox);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.spriteImageBox);
			this.splitContainer1.Size = new System.Drawing.Size(637, 362);
			this.splitContainer1.SplitterDistance = 420;
			this.splitContainer1.TabIndex = 0;
			// 
			// spriteListBox
			// 
			this.spriteListBox.CheckOnClick = true;
			this.spriteListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteListBox.FormattingEnabled = true;
			this.spriteListBox.Location = new System.Drawing.Point(0, 0);
			this.spriteListBox.Name = "spriteListBox";
			this.spriteListBox.Size = new System.Drawing.Size(420, 362);
			this.spriteListBox.TabIndex = 1;
			this.spriteListBox.SelectedIndexChanged += new System.EventHandler(this.spriteListBox_SelectedIndexChanged);
			// 
			// spriteImageBox
			// 
			this.spriteImageBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteImageBox.Location = new System.Drawing.Point(0, 0);
			this.spriteImageBox.Name = "spriteImageBox";
			this.spriteImageBox.Size = new System.Drawing.Size(213, 362);
			this.spriteImageBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
			this.spriteImageBox.TabIndex = 0;
			this.spriteImageBox.TabStop = false;
			// 
			// AddAnimationDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(637, 506);
			this.Controls.Add(this.panel9);
			this.Controls.Add(this.panel2);
			this.Controls.Add(this.panel1);
			this.Name = "AddAnimationDialog";
			this.Text = "AddAnimationDialog";
			this.panel1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.panel10.ResumeLayout(false);
			this.panel10.PerformLayout();
			this.panel11.ResumeLayout(false);
			this.panel11.PerformLayout();
			this.panel12.ResumeLayout(false);
			this.panel12.PerformLayout();
			this.panel6.ResumeLayout(false);
			this.panel6.PerformLayout();
			this.panel7.ResumeLayout(false);
			this.panel7.PerformLayout();
			this.panel8.ResumeLayout(false);
			this.panel8.PerformLayout();
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			this.panel5.ResumeLayout(false);
			this.panel5.PerformLayout();
			this.panel4.ResumeLayout(false);
			this.panel4.PerformLayout();
			this.panel9.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.spriteImageBox)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button createButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.CheckBox loopCheckBox;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Panel panel10;
        private System.Windows.Forms.Panel panel11;
        private System.Windows.Forms.Panel panel12;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox durationTextBox;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.CheckedListBox spriteListBox;
        private System.Windows.Forms.PictureBox spriteImageBox;
    }
}