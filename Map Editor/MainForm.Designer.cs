namespace MapEditor
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			System.Windows.Forms.ListViewItem listViewItem1 = new System.Windows.Forms.ListViewItem("Player 1", 0);
			System.Windows.Forms.ListViewItem listViewItem2 = new System.Windows.Forms.ListViewItem("Player 2", 1);
			System.Windows.Forms.ListViewItem listViewItem3 = new System.Windows.Forms.ListViewItem("Player 3", 2);
			System.Windows.Forms.ListViewItem listViewItem4 = new System.Windows.Forms.ListViewItem("Player 4", 3);
			System.Windows.Forms.ListViewItem listViewItem5 = new System.Windows.Forms.ListViewItem("Player 5", 4);
			System.Windows.Forms.ListViewItem listViewItem6 = new System.Windows.Forms.ListViewItem("Player 6", 5);
			System.Windows.Forms.ListViewItem listViewItem7 = new System.Windows.Forms.ListViewItem("Player 7", 6);
			System.Windows.Forms.ListViewItem listViewItem8 = new System.Windows.Forms.ListViewItem("Player 8", 7);
			this.splitContainer = new System.Windows.Forms.SplitContainer();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.splitContainer2 = new System.Windows.Forms.SplitContainer();
			this.enemyNameTextBox = new System.Windows.Forms.TextBox();
			this.buttonAddEnemy = new System.Windows.Forms.Button();
			this.enemyListView = new System.Windows.Forms.ListView();
			this.enemyImageList = new System.Windows.Forms.ImageList(this.components);
			this.label6 = new System.Windows.Forms.Label();
			this.respawnPointListView = new System.Windows.Forms.ListView();
			this.respawnPointImageList = new System.Windows.Forms.ImageList(this.components);
			this.label5 = new System.Windows.Forms.Label();
			this.mapTileListView = new System.Windows.Forms.ListView();
			this.label4 = new System.Windows.Forms.Label();
			this.attributePanel = new System.Windows.Forms.Panel();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.tileSizeLabel = new System.Windows.Forms.Label();
			this.mapSizeLabel = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.panel1 = new System.Windows.Forms.Panel();
			this.bgmName = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.scaleTrackBar = new System.Windows.Forms.TrackBar();
			this.mapTileImageList = new System.Windows.Forms.ImageList(this.components);
			this.panel2 = new System.Windows.Forms.Panel();
			this.label7 = new System.Windows.Forms.Label();
			this.panel3 = new System.Windows.Forms.Panel();
			this.collisionLeft = new System.Windows.Forms.CheckBox();
			this.collisionTop = new System.Windows.Forms.CheckBox();
			this.collisionRight = new System.Windows.Forms.CheckBox();
			this.collisionBottom = new System.Windows.Forms.CheckBox();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
			this.splitContainer.Panel1.SuspendLayout();
			this.splitContainer.Panel2.SuspendLayout();
			this.splitContainer.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
			this.splitContainer2.Panel1.SuspendLayout();
			this.splitContainer2.Panel2.SuspendLayout();
			this.splitContainer2.SuspendLayout();
			this.attributePanel.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.panel1.SuspendLayout();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.scaleTrackBar)).BeginInit();
			this.panel2.SuspendLayout();
			this.panel3.SuspendLayout();
			this.SuspendLayout();
			// 
			// splitContainer
			// 
			this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer.Location = new System.Drawing.Point(0, 0);
			this.splitContainer.Name = "splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this.splitContainer.Panel1.Controls.Add(this.menuStrip1);
			// 
			// splitContainer.Panel2
			// 
			this.splitContainer.Panel2.Controls.Add(this.splitContainer2);
			this.splitContainer.Size = new System.Drawing.Size(1006, 686);
			this.splitContainer.SplitterDistance = 615;
			this.splitContainer.TabIndex = 0;
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(615, 24);
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
			this.newToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
			this.newToolStripMenuItem.Text = "New";
			this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
			this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(116, 22);
			this.saveAsToolStripMenuItem.Text = "Save As";
			this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
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
			this.splitContainer2.Panel1.Controls.Add(this.panel3);
			this.splitContainer2.Panel1.Controls.Add(this.label7);
			this.splitContainer2.Panel1.Controls.Add(this.panel2);
			this.splitContainer2.Panel1.Controls.Add(this.enemyListView);
			this.splitContainer2.Panel1.Controls.Add(this.label6);
			this.splitContainer2.Panel1.Controls.Add(this.respawnPointListView);
			this.splitContainer2.Panel1.Controls.Add(this.label5);
			this.splitContainer2.Panel1.Controls.Add(this.mapTileListView);
			this.splitContainer2.Panel1.Controls.Add(this.label4);
			// 
			// splitContainer2.Panel2
			// 
			this.splitContainer2.Panel2.Controls.Add(this.attributePanel);
			this.splitContainer2.Size = new System.Drawing.Size(387, 686);
			this.splitContainer2.SplitterDistance = 472;
			this.splitContainer2.TabIndex = 1;
			// 
			// enemyNameTextBox
			// 
			this.enemyNameTextBox.Location = new System.Drawing.Point(194, 6);
			this.enemyNameTextBox.Name = "enemyNameTextBox";
			this.enemyNameTextBox.Size = new System.Drawing.Size(100, 21);
			this.enemyNameTextBox.TabIndex = 8;
			// 
			// buttonAddEnemy
			// 
			this.buttonAddEnemy.Location = new System.Drawing.Point(300, 6);
			this.buttonAddEnemy.Name = "buttonAddEnemy";
			this.buttonAddEnemy.Size = new System.Drawing.Size(75, 23);
			this.buttonAddEnemy.TabIndex = 7;
			this.buttonAddEnemy.Text = "ADD";
			this.buttonAddEnemy.UseVisualStyleBackColor = true;
			this.buttonAddEnemy.Click += new System.EventHandler(this.buttonAddEnemy_Click);
			// 
			// enemyListView
			// 
			this.enemyListView.Dock = System.Windows.Forms.DockStyle.Top;
			this.enemyListView.LargeImageList = this.enemyImageList;
			this.enemyListView.Location = new System.Drawing.Point(0, 265);
			this.enemyListView.MultiSelect = false;
			this.enemyListView.Name = "enemyListView";
			this.enemyListView.Size = new System.Drawing.Size(387, 92);
			this.enemyListView.TabIndex = 6;
			this.enemyListView.UseCompatibleStateImageBehavior = false;
			this.enemyListView.SelectedIndexChanged += new System.EventHandler(this.enemyListView_SelectedIndexChanged);
			// 
			// enemyImageList
			// 
			this.enemyImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("enemyImageList.ImageStream")));
			this.enemyImageList.TransparentColor = System.Drawing.Color.Transparent;
			this.enemyImageList.Images.SetKeyName(0, "scythe.png");
			// 
			// label6
			// 
			this.label6.Dock = System.Windows.Forms.DockStyle.Top;
			this.label6.Location = new System.Drawing.Point(0, 233);
			this.label6.Name = "label6";
			this.label6.Padding = new System.Windows.Forms.Padding(0, 10, 0, 10);
			this.label6.Size = new System.Drawing.Size(387, 32);
			this.label6.TabIndex = 5;
			this.label6.Text = "Enemy";
			// 
			// respawnPointListView
			// 
			this.respawnPointListView.Dock = System.Windows.Forms.DockStyle.Top;
			this.respawnPointListView.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
            listViewItem1,
            listViewItem2,
            listViewItem3,
            listViewItem4,
            listViewItem5,
            listViewItem6,
            listViewItem7,
            listViewItem8});
			this.respawnPointListView.LargeImageList = this.respawnPointImageList;
			this.respawnPointListView.Location = new System.Drawing.Point(0, 164);
			this.respawnPointListView.MultiSelect = false;
			this.respawnPointListView.Name = "respawnPointListView";
			this.respawnPointListView.Size = new System.Drawing.Size(387, 69);
			this.respawnPointListView.TabIndex = 4;
			this.respawnPointListView.UseCompatibleStateImageBehavior = false;
			this.respawnPointListView.SelectedIndexChanged += new System.EventHandler(this.respawnPointListView_SelectedIndexChanged);
			this.respawnPointListView.Click += new System.EventHandler(this.respawnPointListView_Click);
			// 
			// respawnPointImageList
			// 
			this.respawnPointImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("respawnPointImageList.ImageStream")));
			this.respawnPointImageList.TransparentColor = System.Drawing.Color.Transparent;
			this.respawnPointImageList.Images.SetKeyName(0, "placeholder (8).png");
			this.respawnPointImageList.Images.SetKeyName(1, "placeholder (9).png");
			this.respawnPointImageList.Images.SetKeyName(2, "placeholder (10).png");
			this.respawnPointImageList.Images.SetKeyName(3, "placeholder (11).png");
			this.respawnPointImageList.Images.SetKeyName(4, "placeholder (12).png");
			this.respawnPointImageList.Images.SetKeyName(5, "placeholder (13).png");
			this.respawnPointImageList.Images.SetKeyName(6, "placeholder (14).png");
			this.respawnPointImageList.Images.SetKeyName(7, "placeholder (15).png");
			// 
			// label5
			// 
			this.label5.Dock = System.Windows.Forms.DockStyle.Top;
			this.label5.Location = new System.Drawing.Point(0, 132);
			this.label5.Name = "label5";
			this.label5.Padding = new System.Windows.Forms.Padding(0, 10, 0, 10);
			this.label5.Size = new System.Drawing.Size(387, 32);
			this.label5.TabIndex = 3;
			this.label5.Text = "Respawn Point";
			// 
			// mapTileListView
			// 
			this.mapTileListView.Dock = System.Windows.Forms.DockStyle.Top;
			this.mapTileListView.Location = new System.Drawing.Point(0, 32);
			this.mapTileListView.MultiSelect = false;
			this.mapTileListView.Name = "mapTileListView";
			this.mapTileListView.Size = new System.Drawing.Size(387, 100);
			this.mapTileListView.TabIndex = 2;
			this.mapTileListView.UseCompatibleStateImageBehavior = false;
			this.mapTileListView.SelectedIndexChanged += new System.EventHandler(this.mapTileListView_SelectedIndexChanged);
			this.mapTileListView.Click += new System.EventHandler(this.mapTileListView_Click);
			// 
			// label4
			// 
			this.label4.Dock = System.Windows.Forms.DockStyle.Top;
			this.label4.Location = new System.Drawing.Point(0, 0);
			this.label4.Name = "label4";
			this.label4.Padding = new System.Windows.Forms.Padding(0, 10, 0, 10);
			this.label4.Size = new System.Drawing.Size(387, 32);
			this.label4.TabIndex = 1;
			this.label4.Text = "Map Tile";
			// 
			// attributePanel
			// 
			this.attributePanel.Controls.Add(this.groupBox2);
			this.attributePanel.Controls.Add(this.panel1);
			this.attributePanel.Controls.Add(this.groupBox1);
			this.attributePanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.attributePanel.Location = new System.Drawing.Point(0, 0);
			this.attributePanel.Name = "attributePanel";
			this.attributePanel.Size = new System.Drawing.Size(387, 210);
			this.attributePanel.TabIndex = 0;
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.tileSizeLabel);
			this.groupBox2.Controls.Add(this.mapSizeLabel);
			this.groupBox2.Controls.Add(this.label2);
			this.groupBox2.Controls.Add(this.label1);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox2.Location = new System.Drawing.Point(0, 100);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(387, 110);
			this.groupBox2.TabIndex = 4;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Attributes";
			// 
			// tileSizeLabel
			// 
			this.tileSizeLabel.AutoSize = true;
			this.tileSizeLabel.Location = new System.Drawing.Point(71, 53);
			this.tileSizeLabel.Name = "tileSizeLabel";
			this.tileSizeLabel.Size = new System.Drawing.Size(0, 12);
			this.tileSizeLabel.TabIndex = 1;
			// 
			// mapSizeLabel
			// 
			this.mapSizeLabel.AutoSize = true;
			this.mapSizeLabel.Location = new System.Drawing.Point(71, 29);
			this.mapSizeLabel.Name = "mapSizeLabel";
			this.mapSizeLabel.Size = new System.Drawing.Size(0, 12);
			this.mapSizeLabel.TabIndex = 1;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 29);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(58, 12);
			this.label2.TabIndex = 0;
			this.label2.Text = "Map size";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 53);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(54, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "Tile size";
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.bgmName);
			this.panel1.Controls.Add(this.label3);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel1.Location = new System.Drawing.Point(0, 65);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(387, 35);
			this.panel1.TabIndex = 3;
			// 
			// bgmName
			// 
			this.bgmName.Location = new System.Drawing.Point(79, 6);
			this.bgmName.Name = "bgmName";
			this.bgmName.Size = new System.Drawing.Size(188, 21);
			this.bgmName.TabIndex = 6;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(3, 10);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(69, 12);
			this.label3.TabIndex = 5;
			this.label3.Text = "BGM name";
			// 
			// groupBox1
			// 
			this.groupBox1.AutoSize = true;
			this.groupBox1.Controls.Add(this.scaleTrackBar);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(387, 65);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Scale";
			// 
			// scaleTrackBar
			// 
			this.scaleTrackBar.Dock = System.Windows.Forms.DockStyle.Top;
			this.scaleTrackBar.Location = new System.Drawing.Point(3, 17);
			this.scaleTrackBar.Maximum = 100;
			this.scaleTrackBar.Minimum = 10;
			this.scaleTrackBar.Name = "scaleTrackBar";
			this.scaleTrackBar.Size = new System.Drawing.Size(381, 45);
			this.scaleTrackBar.TabIndex = 0;
			this.scaleTrackBar.Value = 10;
			this.scaleTrackBar.Scroll += new System.EventHandler(this.scaleTrackBar_Scroll);
			// 
			// mapTileImageList
			// 
			this.mapTileImageList.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
			this.mapTileImageList.ImageSize = new System.Drawing.Size(16, 16);
			this.mapTileImageList.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// panel2
			// 
			this.panel2.AutoSize = true;
			this.panel2.Controls.Add(this.enemyNameTextBox);
			this.panel2.Controls.Add(this.buttonAddEnemy);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel2.Location = new System.Drawing.Point(0, 357);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(387, 32);
			this.panel2.TabIndex = 9;
			// 
			// label7
			// 
			this.label7.Dock = System.Windows.Forms.DockStyle.Top;
			this.label7.Location = new System.Drawing.Point(0, 389);
			this.label7.Name = "label7";
			this.label7.Padding = new System.Windows.Forms.Padding(0, 10, 0, 10);
			this.label7.Size = new System.Drawing.Size(387, 32);
			this.label7.TabIndex = 10;
			this.label7.Text = "Collision Flags";
			// 
			// panel3
			// 
			this.panel3.AutoSize = true;
			this.panel3.Controls.Add(this.collisionBottom);
			this.panel3.Controls.Add(this.collisionRight);
			this.panel3.Controls.Add(this.collisionTop);
			this.panel3.Controls.Add(this.collisionLeft);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel3.Location = new System.Drawing.Point(0, 421);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(387, 23);
			this.panel3.TabIndex = 11;
			// 
			// collisionLeft
			// 
			this.collisionLeft.AutoSize = true;
			this.collisionLeft.Location = new System.Drawing.Point(8, 4);
			this.collisionLeft.Name = "collisionLeft";
			this.collisionLeft.Size = new System.Drawing.Size(44, 16);
			this.collisionLeft.TabIndex = 0;
			this.collisionLeft.Text = "Left";
			this.collisionLeft.UseVisualStyleBackColor = true;
			// 
			// collisionTop
			// 
			this.collisionTop.AutoSize = true;
			this.collisionTop.Location = new System.Drawing.Point(58, 4);
			this.collisionTop.Name = "collisionTop";
			this.collisionTop.Size = new System.Drawing.Size(46, 16);
			this.collisionTop.TabIndex = 0;
			this.collisionTop.Text = "Top";
			this.collisionTop.UseVisualStyleBackColor = true;
			// 
			// collisionRight
			// 
			this.collisionRight.AutoSize = true;
			this.collisionRight.Location = new System.Drawing.Point(110, 3);
			this.collisionRight.Name = "collisionRight";
			this.collisionRight.Size = new System.Drawing.Size(52, 16);
			this.collisionRight.TabIndex = 0;
			this.collisionRight.Text = "Right";
			this.collisionRight.UseVisualStyleBackColor = true;
			// 
			// collisionBottom
			// 
			this.collisionBottom.AutoSize = true;
			this.collisionBottom.Location = new System.Drawing.Point(168, 4);
			this.collisionBottom.Name = "collisionBottom";
			this.collisionBottom.Size = new System.Drawing.Size(63, 16);
			this.collisionBottom.TabIndex = 0;
			this.collisionBottom.Text = "Bottom";
			this.collisionBottom.UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1006, 686);
			this.Controls.Add(this.splitContainer);
			this.Name = "MainForm";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.splitContainer.Panel1.ResumeLayout(false);
			this.splitContainer.Panel1.PerformLayout();
			this.splitContainer.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
			this.splitContainer.ResumeLayout(false);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.splitContainer2.Panel1.ResumeLayout(false);
			this.splitContainer2.Panel1.PerformLayout();
			this.splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
			this.splitContainer2.ResumeLayout(false);
			this.attributePanel.ResumeLayout(false);
			this.attributePanel.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.panel1.PerformLayout();
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.scaleTrackBar)).EndInit();
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.Panel attributePanel;
        private System.Windows.Forms.ImageList mapTileImageList;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TrackBar scaleTrackBar;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label tileSizeLabel;
		private System.Windows.Forms.Label mapSizeLabel;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.TextBox bgmName;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ListView mapTileListView;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.ListView enemyListView;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.ListView respawnPointListView;
		private System.Windows.Forms.ImageList respawnPointImageList;
		private System.Windows.Forms.ImageList enemyImageList;
		private System.Windows.Forms.Button buttonAddEnemy;
		private System.Windows.Forms.TextBox enemyNameTextBox;
		private System.Windows.Forms.Panel panel3;
		private System.Windows.Forms.CheckBox collisionBottom;
		private System.Windows.Forms.CheckBox collisionRight;
		private System.Windows.Forms.CheckBox collisionTop;
		private System.Windows.Forms.CheckBox collisionLeft;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Panel panel2;
	}
}

