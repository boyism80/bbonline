namespace WindowEditor
{
    partial class SubWindowAttrDialog
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
			this.SubWindowIdTextBox = new System.Windows.Forms.TextBox();
			this.SubWindowHeightTextBox = new System.Windows.Forms.TextBox();
			this.SubWindowWidthTextBox = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.SubWindowPurposeComboBox = new System.Windows.Forms.ComboBox();
			this.SubWindowTextTextBox = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.UseImageCheckBox = new System.Windows.Forms.CheckBox();
			this.SubWindowYTextBox = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.SubWindowXTextBox = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.InvisibleCheckBox = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// OKButton
			// 
			this.OKButton.Location = new System.Drawing.Point(302, 221);
			this.OKButton.Name = "OKButton";
			this.OKButton.Size = new System.Drawing.Size(75, 23);
			this.OKButton.TabIndex = 19;
			this.OKButton.Text = "OK";
			this.OKButton.UseVisualStyleBackColor = true;
			this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// cancelButton
			// 
			this.cancelButton.Location = new System.Drawing.Point(383, 221);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(75, 23);
			this.cancelButton.TabIndex = 20;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
			// 
			// SubWindowIdTextBox
			// 
			this.SubWindowIdTextBox.Location = new System.Drawing.Point(302, 71);
			this.SubWindowIdTextBox.Name = "SubWindowIdTextBox";
			this.SubWindowIdTextBox.Size = new System.Drawing.Size(100, 21);
			this.SubWindowIdTextBox.TabIndex = 18;
			// 
			// SubWindowHeightTextBox
			// 
			this.SubWindowHeightTextBox.Location = new System.Drawing.Point(89, 144);
			this.SubWindowHeightTextBox.Name = "SubWindowHeightTextBox";
			this.SubWindowHeightTextBox.Size = new System.Drawing.Size(100, 21);
			this.SubWindowHeightTextBox.TabIndex = 17;
			this.SubWindowHeightTextBox.Text = "60";
			// 
			// SubWindowWidthTextBox
			// 
			this.SubWindowWidthTextBox.Location = new System.Drawing.Point(89, 107);
			this.SubWindowWidthTextBox.Name = "SubWindowWidthTextBox";
			this.SubWindowWidthTextBox.Size = new System.Drawing.Size(100, 21);
			this.SubWindowWidthTextBox.TabIndex = 16;
			this.SubWindowWidthTextBox.Text = "80";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(271, 74);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(15, 12);
			this.label3.TabIndex = 15;
			this.label3.Text = "Id";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(40, 147);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(40, 12);
			this.label2.TabIndex = 14;
			this.label2.Text = "Height";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(45, 110);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 12);
			this.label1.TabIndex = 13;
			this.label1.Text = "Width";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(234, 108);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(52, 12);
			this.label4.TabIndex = 21;
			this.label4.Text = "Purpose";
			// 
			// SubWindowPurposeComboBox
			// 
			this.SubWindowPurposeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SubWindowPurposeComboBox.FormattingEnabled = true;
			this.SubWindowPurposeComboBox.Items.AddRange(new object[] {
            "Button",
            "EditText",
            "Label",
            "Window"});
			this.SubWindowPurposeComboBox.Location = new System.Drawing.Point(302, 105);
			this.SubWindowPurposeComboBox.Name = "SubWindowPurposeComboBox";
			this.SubWindowPurposeComboBox.Size = new System.Drawing.Size(100, 20);
			this.SubWindowPurposeComboBox.TabIndex = 22;
			this.SubWindowPurposeComboBox.SelectedIndexChanged += new System.EventHandler(this.SubWindowPurposeComboBox_SelectedIndexChanged);
			// 
			// SubWindowTextTextBox
			// 
			this.SubWindowTextTextBox.Location = new System.Drawing.Point(89, 184);
			this.SubWindowTextTextBox.Name = "SubWindowTextTextBox";
			this.SubWindowTextTextBox.Size = new System.Drawing.Size(172, 21);
			this.SubWindowTextTextBox.TabIndex = 24;
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(50, 187);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(30, 12);
			this.label5.TabIndex = 23;
			this.label5.Text = "Text";
			// 
			// UseImageCheckBox
			// 
			this.UseImageCheckBox.AutoSize = true;
			this.UseImageCheckBox.Checked = true;
			this.UseImageCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
			this.UseImageCheckBox.Location = new System.Drawing.Point(302, 189);
			this.UseImageCheckBox.Name = "UseImageCheckBox";
			this.UseImageCheckBox.Size = new System.Drawing.Size(116, 16);
			this.UseImageCheckBox.TabIndex = 25;
			this.UseImageCheckBox.Text = "이미지 사용 여부";
			this.UseImageCheckBox.UseVisualStyleBackColor = true;
			// 
			// SubWindowYTextBox
			// 
			this.SubWindowYTextBox.Location = new System.Drawing.Point(89, 71);
			this.SubWindowYTextBox.Name = "SubWindowYTextBox";
			this.SubWindowYTextBox.Size = new System.Drawing.Size(100, 21);
			this.SubWindowYTextBox.TabIndex = 27;
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(67, 74);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(13, 12);
			this.label6.TabIndex = 26;
			this.label6.Text = "Y";
			// 
			// SubWindowXTextBox
			// 
			this.SubWindowXTextBox.Location = new System.Drawing.Point(89, 32);
			this.SubWindowXTextBox.Name = "SubWindowXTextBox";
			this.SubWindowXTextBox.Size = new System.Drawing.Size(100, 21);
			this.SubWindowXTextBox.TabIndex = 29;
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(67, 35);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(13, 12);
			this.label7.TabIndex = 28;
			this.label7.Text = "X";
			// 
			// InvisibleCheckBox
			// 
			this.InvisibleCheckBox.AutoSize = true;
			this.InvisibleCheckBox.Checked = true;
			this.InvisibleCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
			this.InvisibleCheckBox.Location = new System.Drawing.Point(302, 167);
			this.InvisibleCheckBox.Name = "InvisibleCheckBox";
			this.InvisibleCheckBox.Size = new System.Drawing.Size(60, 16);
			this.InvisibleCheckBox.TabIndex = 30;
			this.InvisibleCheckBox.Text = "보이기";
			this.InvisibleCheckBox.UseVisualStyleBackColor = true;
			// 
			// SubWindowAttrDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(471, 264);
			this.Controls.Add(this.InvisibleCheckBox);
			this.Controls.Add(this.SubWindowXTextBox);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.SubWindowYTextBox);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.UseImageCheckBox);
			this.Controls.Add(this.SubWindowTextTextBox);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.SubWindowPurposeComboBox);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.OKButton);
			this.Controls.Add(this.cancelButton);
			this.Controls.Add(this.SubWindowIdTextBox);
			this.Controls.Add(this.SubWindowHeightTextBox);
			this.Controls.Add(this.SubWindowWidthTextBox);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Name = "SubWindowAttrDialog";
			this.Text = "SubWindowAttrDialog";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button OKButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox SubWindowIdTextBox;
        private System.Windows.Forms.TextBox SubWindowHeightTextBox;
        private System.Windows.Forms.TextBox SubWindowWidthTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox SubWindowPurposeComboBox;
        private System.Windows.Forms.TextBox SubWindowTextTextBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox UseImageCheckBox;
        private System.Windows.Forms.TextBox SubWindowYTextBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox SubWindowXTextBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox InvisibleCheckBox;
    }
}