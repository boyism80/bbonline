namespace MapEditor
{
	partial class MapAttrDialog
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
			this.columnsTextBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.rowsTextBox = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.tileHeightTextBox = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.tileWidthTextBox = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.cancelButton = new System.Windows.Forms.Button();
			this.OKButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// columnsTextBox
			// 
			this.columnsTextBox.Location = new System.Drawing.Point(307, 52);
			this.columnsTextBox.Name = "columnsTextBox";
			this.columnsTextBox.ReadOnly = true;
			this.columnsTextBox.Size = new System.Drawing.Size(100, 21);
			this.columnsTextBox.TabIndex = 3;
			this.columnsTextBox.Text = "40";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(249, 57);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(56, 12);
			this.label1.TabIndex = 2;
			this.label1.Text = "Columns";
			// 
			// rowsTextBox
			// 
			this.rowsTextBox.Location = new System.Drawing.Point(139, 52);
			this.rowsTextBox.Name = "rowsTextBox";
			this.rowsTextBox.ReadOnly = true;
			this.rowsTextBox.Size = new System.Drawing.Size(100, 21);
			this.rowsTextBox.TabIndex = 5;
			this.rowsTextBox.Text = "26";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(86, 57);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(37, 12);
			this.label2.TabIndex = 4;
			this.label2.Text = "Rows";
			// 
			// tileHeightTextBox
			// 
			this.tileHeightTextBox.Location = new System.Drawing.Point(307, 79);
			this.tileHeightTextBox.Name = "tileHeightTextBox";
			this.tileHeightTextBox.ReadOnly = true;
			this.tileHeightTextBox.Size = new System.Drawing.Size(100, 21);
			this.tileHeightTextBox.TabIndex = 9;
			this.tileHeightTextBox.Text = "8";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(249, 84);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(48, 12);
			this.label3.TabIndex = 8;
			this.label3.Text = "THeight";
			// 
			// tileWidthTextBox
			// 
			this.tileWidthTextBox.Location = new System.Drawing.Point(139, 79);
			this.tileWidthTextBox.Name = "tileWidthTextBox";
			this.tileWidthTextBox.ReadOnly = true;
			this.tileWidthTextBox.Size = new System.Drawing.Size(100, 21);
			this.tileWidthTextBox.TabIndex = 7;
			this.tileWidthTextBox.Text = "8";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(86, 84);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(43, 12);
			this.label4.TabIndex = 6;
			this.label4.Text = "TWidth";
			// 
			// cancelButton
			// 
			this.cancelButton.Location = new System.Drawing.Point(397, 121);
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size(75, 23);
			this.cancelButton.TabIndex = 10;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			this.cancelButton.Click += new System.EventHandler(this.cancelButton_Click);
			// 
			// OKButton
			// 
			this.OKButton.Location = new System.Drawing.Point(316, 121);
			this.OKButton.Name = "OKButton";
			this.OKButton.Size = new System.Drawing.Size(75, 23);
			this.OKButton.TabIndex = 10;
			this.OKButton.Text = "OK";
			this.OKButton.UseVisualStyleBackColor = true;
			this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
			// 
			// MapAttrDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(484, 156);
			this.Controls.Add(this.OKButton);
			this.Controls.Add(this.cancelButton);
			this.Controls.Add(this.tileHeightTextBox);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.tileWidthTextBox);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.rowsTextBox);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.columnsTextBox);
			this.Controls.Add(this.label1);
			this.MaximizeBox = false;
			this.Name = "MapAttrDialog";
			this.Text = "MapAttrDialoog";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox columnsTextBox;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox rowsTextBox;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox tileHeightTextBox;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox tileWidthTextBox;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button cancelButton;
		private System.Windows.Forms.Button OKButton;
	}
}