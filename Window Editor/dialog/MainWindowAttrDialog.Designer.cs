namespace WindowEditor
{
    partial class MainWindowAttrDialog
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
            this.OKButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.MainWindowHeightTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.MainWindowWidthTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // OKButton
            // 
            this.OKButton.Location = new System.Drawing.Point(311, 121);
            this.OKButton.Name = "OKButton";
            this.OKButton.Size = new System.Drawing.Size(75, 23);
            this.OKButton.TabIndex = 15;
            this.OKButton.Text = "OK";
            this.OKButton.UseVisualStyleBackColor = true;
            this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
            // 
            // cancelButton
            // 
            this.cancelButton.Location = new System.Drawing.Point(392, 121);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 16;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
            // 
            // MainWindowHeightTextBox
            // 
            this.MainWindowHeightTextBox.Location = new System.Drawing.Point(329, 63);
            this.MainWindowHeightTextBox.Name = "MainWindowHeightTextBox";
            this.MainWindowHeightTextBox.Size = new System.Drawing.Size(100, 21);
            this.MainWindowHeightTextBox.TabIndex = 14;
            this.MainWindowHeightTextBox.Text = "208";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(239, 68);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 12);
            this.label3.TabIndex = 13;
            this.label3.Text = "WindowHeight";
            // 
            // MainWindowWidthTextBox
            // 
            this.MainWindowWidthTextBox.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.MainWindowWidthTextBox.Location = new System.Drawing.Point(129, 63);
            this.MainWindowWidthTextBox.Name = "MainWindowWidthTextBox";
            this.MainWindowWidthTextBox.Size = new System.Drawing.Size(100, 21);
            this.MainWindowWidthTextBox.TabIndex = 12;
            this.MainWindowWidthTextBox.Text = "320";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(44, 68);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "WindowWidth";
            // 
            // MainWindowAttrDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(484, 156);
            this.Controls.Add(this.OKButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.MainWindowHeightTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.MainWindowWidthTextBox);
            this.Controls.Add(this.label4);
            this.Name = "MainWindowAttrDialog";
            this.Text = "MainWindowAttrDialog";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox MainWindowHeightTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox MainWindowWidthTextBox;
        private System.Windows.Forms.Label label4;
    }
}