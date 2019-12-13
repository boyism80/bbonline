namespace SpriteEditor
{
    partial class PBSpriteManager
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
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.spriteTab = new System.Windows.Forms.TabPage();
			this.mainSplitContainer = new System.Windows.Forms.SplitContainer();
			this.splitContainer2 = new System.Windows.Forms.SplitContainer();
			this.spriteGridView = new System.Windows.Forms.DataGridView();
			this.spriteNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.panel2 = new System.Windows.Forms.Panel();
			this.panel9 = new System.Windows.Forms.Panel();
			this.panel10 = new System.Windows.Forms.Panel();
			this.pivots = new System.Windows.Forms.ComboBox();
			this.panel11 = new System.Windows.Forms.Panel();
			this.label3 = new System.Windows.Forms.Label();
			this.panel4 = new System.Windows.Forms.Panel();
			this.panel5 = new System.Windows.Forms.Panel();
			this.spriteSizeTextBox = new System.Windows.Forms.TextBox();
			this.panel6 = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.panel3 = new System.Windows.Forms.Panel();
			this.panel7 = new System.Windows.Forms.Panel();
			this.spriteNameTextBox = new System.Windows.Forms.TextBox();
			this.panel8 = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.panel1 = new System.Windows.Forms.Panel();
			this.loadSpriteButton = new System.Windows.Forms.Button();
			this.applyButton = new System.Windows.Forms.Button();
			this.canvasPanel = new System.Windows.Forms.Panel();
			this.splitTab = new System.Windows.Forms.TabPage();
			this.panel12 = new System.Windows.Forms.Panel();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.spriteSheetPanel = new SpriteEditor.SpriteSheetPanel();
			this.panel14 = new System.Windows.Forms.Panel();
			this.zoomScale = new System.Windows.Forms.TextBox();
			this.drawGrid = new System.Windows.Forms.CheckBox();
			this.gridHeight = new System.Windows.Forms.TextBox();
			this.gridY = new System.Windows.Forms.TextBox();
			this.gridColumns = new System.Windows.Forms.TextBox();
			this.gridWidth = new System.Windows.Forms.TextBox();
			this.gridX = new System.Windows.Forms.TextBox();
			this.gridRows = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.panel13 = new System.Windows.Forms.Panel();
			this.buttonLoadSpriteSheet = new System.Windows.Forms.Button();
			this.buttonSave = new System.Windows.Forms.Button();
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.tabControl1.SuspendLayout();
			this.spriteTab.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).BeginInit();
			this.mainSplitContainer.Panel1.SuspendLayout();
			this.mainSplitContainer.Panel2.SuspendLayout();
			this.mainSplitContainer.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
			this.splitContainer2.Panel1.SuspendLayout();
			this.splitContainer2.Panel2.SuspendLayout();
			this.splitContainer2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.spriteGridView)).BeginInit();
			this.panel2.SuspendLayout();
			this.panel9.SuspendLayout();
			this.panel10.SuspendLayout();
			this.panel11.SuspendLayout();
			this.panel4.SuspendLayout();
			this.panel5.SuspendLayout();
			this.panel6.SuspendLayout();
			this.panel3.SuspendLayout();
			this.panel7.SuspendLayout();
			this.panel8.SuspendLayout();
			this.panel1.SuspendLayout();
			this.splitTab.SuspendLayout();
			this.panel12.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.panel14.SuspendLayout();
			this.panel13.SuspendLayout();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.spriteTab);
			this.tabControl1.Controls.Add(this.splitTab);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 24);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(1092, 659);
			this.tabControl1.TabIndex = 0;
			// 
			// spriteTab
			// 
			this.spriteTab.Controls.Add(this.mainSplitContainer);
			this.spriteTab.Location = new System.Drawing.Point(4, 22);
			this.spriteTab.Name = "spriteTab";
			this.spriteTab.Padding = new System.Windows.Forms.Padding(3);
			this.spriteTab.Size = new System.Drawing.Size(1084, 633);
			this.spriteTab.TabIndex = 0;
			this.spriteTab.Text = "Sprite";
			this.spriteTab.UseVisualStyleBackColor = true;
			// 
			// mainSplitContainer
			// 
			this.mainSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
			this.mainSplitContainer.Location = new System.Drawing.Point(3, 3);
			this.mainSplitContainer.Name = "mainSplitContainer";
			// 
			// mainSplitContainer.Panel1
			// 
			this.mainSplitContainer.Panel1.Controls.Add(this.splitContainer2);
			// 
			// mainSplitContainer.Panel2
			// 
			this.mainSplitContainer.Panel2.Controls.Add(this.canvasPanel);
			this.mainSplitContainer.Size = new System.Drawing.Size(1078, 627);
			this.mainSplitContainer.SplitterDistance = 359;
			this.mainSplitContainer.TabIndex = 0;
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
			this.splitContainer2.Panel1.Controls.Add(this.spriteGridView);
			this.splitContainer2.Panel1.Padding = new System.Windows.Forms.Padding(5);
			// 
			// splitContainer2.Panel2
			// 
			this.splitContainer2.Panel2.Controls.Add(this.panel2);
			this.splitContainer2.Panel2.Controls.Add(this.panel1);
			this.splitContainer2.Size = new System.Drawing.Size(359, 627);
			this.splitContainer2.SplitterDistance = 445;
			this.splitContainer2.TabIndex = 0;
			// 
			// spriteGridView
			// 
			this.spriteGridView.AllowUserToAddRows = false;
			this.spriteGridView.AllowUserToDeleteRows = false;
			this.spriteGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.spriteGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.spriteGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.spriteNameColumn});
			this.spriteGridView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteGridView.Location = new System.Drawing.Point(5, 5);
			this.spriteGridView.Name = "spriteGridView";
			this.spriteGridView.ReadOnly = true;
			this.spriteGridView.RowTemplate.Height = 23;
			this.spriteGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this.spriteGridView.Size = new System.Drawing.Size(349, 435);
			this.spriteGridView.TabIndex = 0;
			this.spriteGridView.SelectionChanged += new System.EventHandler(this.spriteGridView_SelectionChanged);
			// 
			// spriteNameColumn
			// 
			this.spriteNameColumn.HeaderText = "Name";
			this.spriteNameColumn.Name = "spriteNameColumn";
			this.spriteNameColumn.ReadOnly = true;
			// 
			// panel2
			// 
			this.panel2.Controls.Add(this.panel9);
			this.panel2.Controls.Add(this.panel4);
			this.panel2.Controls.Add(this.panel3);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel2.Location = new System.Drawing.Point(0, 0);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(359, 137);
			this.panel2.TabIndex = 2;
			// 
			// panel9
			// 
			this.panel9.Controls.Add(this.panel10);
			this.panel9.Controls.Add(this.panel11);
			this.panel9.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel9.Location = new System.Drawing.Point(0, 72);
			this.panel9.Name = "panel9";
			this.panel9.Size = new System.Drawing.Size(359, 36);
			this.panel9.TabIndex = 4;
			// 
			// panel10
			// 
			this.panel10.AutoSize = true;
			this.panel10.Controls.Add(this.pivots);
			this.panel10.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel10.Location = new System.Drawing.Point(63, 0);
			this.panel10.Name = "panel10";
			this.panel10.Padding = new System.Windows.Forms.Padding(5);
			this.panel10.Size = new System.Drawing.Size(296, 36);
			this.panel10.TabIndex = 1;
			// 
			// pivots
			// 
			this.pivots.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pivots.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.pivots.FormattingEnabled = true;
			this.pivots.Items.AddRange(new object[] {
            "LeftTop",
            "LeftBottom",
            "RightTop",
            "RightBottom",
            "CenterTop",
            "CetnerBottom"});
			this.pivots.Location = new System.Drawing.Point(5, 5);
			this.pivots.Name = "pivots";
			this.pivots.Size = new System.Drawing.Size(286, 20);
			this.pivots.TabIndex = 0;
			// 
			// panel11
			// 
			this.panel11.Controls.Add(this.label3);
			this.panel11.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel11.Location = new System.Drawing.Point(0, 0);
			this.panel11.Name = "panel11";
			this.panel11.Size = new System.Drawing.Size(63, 36);
			this.panel11.TabIndex = 0;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(5, 9);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(32, 12);
			this.label3.TabIndex = 1;
			this.label3.Text = "Pivot";
			// 
			// panel4
			// 
			this.panel4.Controls.Add(this.panel5);
			this.panel4.Controls.Add(this.panel6);
			this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel4.Location = new System.Drawing.Point(0, 36);
			this.panel4.Name = "panel4";
			this.panel4.Size = new System.Drawing.Size(359, 36);
			this.panel4.TabIndex = 3;
			// 
			// panel5
			// 
			this.panel5.AutoSize = true;
			this.panel5.Controls.Add(this.spriteSizeTextBox);
			this.panel5.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel5.Location = new System.Drawing.Point(63, 0);
			this.panel5.Name = "panel5";
			this.panel5.Padding = new System.Windows.Forms.Padding(5);
			this.panel5.Size = new System.Drawing.Size(296, 36);
			this.panel5.TabIndex = 1;
			// 
			// spriteSizeTextBox
			// 
			this.spriteSizeTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteSizeTextBox.Location = new System.Drawing.Point(5, 5);
			this.spriteSizeTextBox.Name = "spriteSizeTextBox";
			this.spriteSizeTextBox.ReadOnly = true;
			this.spriteSizeTextBox.Size = new System.Drawing.Size(286, 21);
			this.spriteSizeTextBox.TabIndex = 0;
			// 
			// panel6
			// 
			this.panel6.Controls.Add(this.label2);
			this.panel6.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel6.Location = new System.Drawing.Point(0, 0);
			this.panel6.Name = "panel6";
			this.panel6.Size = new System.Drawing.Size(63, 36);
			this.panel6.TabIndex = 0;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(5, 9);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(30, 12);
			this.label2.TabIndex = 1;
			this.label2.Text = "Size";
			// 
			// panel3
			// 
			this.panel3.Controls.Add(this.panel7);
			this.panel3.Controls.Add(this.panel8);
			this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel3.Location = new System.Drawing.Point(0, 0);
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size(359, 36);
			this.panel3.TabIndex = 2;
			// 
			// panel7
			// 
			this.panel7.AutoSize = true;
			this.panel7.Controls.Add(this.spriteNameTextBox);
			this.panel7.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel7.Location = new System.Drawing.Point(63, 0);
			this.panel7.Name = "panel7";
			this.panel7.Padding = new System.Windows.Forms.Padding(5);
			this.panel7.Size = new System.Drawing.Size(296, 36);
			this.panel7.TabIndex = 1;
			// 
			// spriteNameTextBox
			// 
			this.spriteNameTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteNameTextBox.Location = new System.Drawing.Point(5, 5);
			this.spriteNameTextBox.Name = "spriteNameTextBox";
			this.spriteNameTextBox.Size = new System.Drawing.Size(286, 21);
			this.spriteNameTextBox.TabIndex = 0;
			// 
			// panel8
			// 
			this.panel8.Controls.Add(this.label1);
			this.panel8.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel8.Location = new System.Drawing.Point(0, 0);
			this.panel8.Name = "panel8";
			this.panel8.Size = new System.Drawing.Size(63, 36);
			this.panel8.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(5, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(39, 12);
			this.label1.TabIndex = 1;
			this.label1.Text = "Name";
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.loadSpriteButton);
			this.panel1.Controls.Add(this.applyButton);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel1.Location = new System.Drawing.Point(0, 137);
			this.panel1.Name = "panel1";
			this.panel1.Padding = new System.Windows.Forms.Padding(10);
			this.panel1.Size = new System.Drawing.Size(359, 41);
			this.panel1.TabIndex = 1;
			// 
			// loadSpriteButton
			// 
			this.loadSpriteButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.loadSpriteButton.Location = new System.Drawing.Point(199, 10);
			this.loadSpriteButton.Name = "loadSpriteButton";
			this.loadSpriteButton.Size = new System.Drawing.Size(75, 21);
			this.loadSpriteButton.TabIndex = 1;
			this.loadSpriteButton.Text = "Load";
			this.loadSpriteButton.UseVisualStyleBackColor = true;
			this.loadSpriteButton.Click += new System.EventHandler(this.loadSpriteButton_Click);
			// 
			// applyButton
			// 
			this.applyButton.Dock = System.Windows.Forms.DockStyle.Right;
			this.applyButton.Location = new System.Drawing.Point(274, 10);
			this.applyButton.Name = "applyButton";
			this.applyButton.Size = new System.Drawing.Size(75, 21);
			this.applyButton.TabIndex = 0;
			this.applyButton.Text = "Apply";
			this.applyButton.UseVisualStyleBackColor = true;
			this.applyButton.Click += new System.EventHandler(this.applyButton_Click);
			// 
			// canvasPanel
			// 
			this.canvasPanel.AutoScroll = true;
			this.canvasPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.canvasPanel.Location = new System.Drawing.Point(0, 0);
			this.canvasPanel.Name = "canvasPanel";
			this.canvasPanel.Size = new System.Drawing.Size(715, 627);
			this.canvasPanel.TabIndex = 0;
			// 
			// splitTab
			// 
			this.splitTab.Controls.Add(this.panel12);
			this.splitTab.Controls.Add(this.panel13);
			this.splitTab.Location = new System.Drawing.Point(4, 22);
			this.splitTab.Name = "splitTab";
			this.splitTab.Padding = new System.Windows.Forms.Padding(3);
			this.splitTab.Size = new System.Drawing.Size(1084, 633);
			this.splitTab.TabIndex = 1;
			this.splitTab.Text = "Split";
			this.splitTab.UseVisualStyleBackColor = true;
			// 
			// panel12
			// 
			this.panel12.Controls.Add(this.splitContainer1);
			this.panel12.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel12.Location = new System.Drawing.Point(3, 3);
			this.panel12.Name = "panel12";
			this.panel12.Size = new System.Drawing.Size(1078, 536);
			this.panel12.TabIndex = 2;
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.spriteSheetPanel);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.panel14);
			this.splitContainer1.Size = new System.Drawing.Size(1078, 536);
			this.splitContainer1.SplitterDistance = 789;
			this.splitContainer1.TabIndex = 0;
			// 
			// spriteSheetPanel
			// 
			this.spriteSheetPanel.Columns = 0;
			this.spriteSheetPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spriteSheetPanel.DrawGrid = false;
			this.spriteSheetPanel.Location = new System.Drawing.Point(0, 0);
			this.spriteSheetPanel.Name = "spriteSheetPanel";
			this.spriteSheetPanel.Rows = 0;
			this.spriteSheetPanel.Scale = 1F;
			this.spriteSheetPanel.Size = new System.Drawing.Size(789, 536);
			this.spriteSheetPanel.Source = null;
			this.spriteSheetPanel.TabIndex = 0;
			// 
			// panel14
			// 
			this.panel14.Controls.Add(this.zoomScale);
			this.panel14.Controls.Add(this.drawGrid);
			this.panel14.Controls.Add(this.gridHeight);
			this.panel14.Controls.Add(this.gridY);
			this.panel14.Controls.Add(this.gridColumns);
			this.panel14.Controls.Add(this.gridWidth);
			this.panel14.Controls.Add(this.gridX);
			this.panel14.Controls.Add(this.gridRows);
			this.panel14.Controls.Add(this.label5);
			this.panel14.Controls.Add(this.label7);
			this.panel14.Controls.Add(this.label8);
			this.panel14.Controls.Add(this.label6);
			this.panel14.Controls.Add(this.label4);
			this.panel14.Dock = System.Windows.Forms.DockStyle.Fill;
			this.panel14.Location = new System.Drawing.Point(0, 0);
			this.panel14.Name = "panel14";
			this.panel14.Size = new System.Drawing.Size(285, 536);
			this.panel14.TabIndex = 0;
			// 
			// zoomScale
			// 
			this.zoomScale.Location = new System.Drawing.Point(76, 169);
			this.zoomScale.Name = "zoomScale";
			this.zoomScale.Size = new System.Drawing.Size(100, 21);
			this.zoomScale.TabIndex = 8;
			this.zoomScale.TextChanged += new System.EventHandler(this.zoomScale_TextChanged);
			// 
			// drawGrid
			// 
			this.drawGrid.AutoSize = true;
			this.drawGrid.Location = new System.Drawing.Point(10, 71);
			this.drawGrid.Name = "drawGrid";
			this.drawGrid.Size = new System.Drawing.Size(80, 16);
			this.drawGrid.TabIndex = 7;
			this.drawGrid.Text = "Draw Grid";
			this.drawGrid.UseVisualStyleBackColor = true;
			this.drawGrid.CheckedChanged += new System.EventHandler(this.drawGrid_CheckedChanged);
			// 
			// gridHeight
			// 
			this.gridHeight.Location = new System.Drawing.Point(163, 122);
			this.gridHeight.Name = "gridHeight";
			this.gridHeight.ReadOnly = true;
			this.gridHeight.Size = new System.Drawing.Size(81, 21);
			this.gridHeight.TabIndex = 5;
			this.gridHeight.Text = "0";
			// 
			// gridY
			// 
			this.gridY.Location = new System.Drawing.Point(163, 95);
			this.gridY.Name = "gridY";
			this.gridY.ReadOnly = true;
			this.gridY.Size = new System.Drawing.Size(81, 21);
			this.gridY.TabIndex = 5;
			this.gridY.Text = "0";
			// 
			// gridColumns
			// 
			this.gridColumns.Location = new System.Drawing.Point(76, 36);
			this.gridColumns.Name = "gridColumns";
			this.gridColumns.Size = new System.Drawing.Size(100, 21);
			this.gridColumns.TabIndex = 5;
			this.gridColumns.Text = "13";
			this.gridColumns.TextChanged += new System.EventHandler(this.gridColumns_TextChanged);
			// 
			// gridWidth
			// 
			this.gridWidth.Location = new System.Drawing.Point(76, 122);
			this.gridWidth.Name = "gridWidth";
			this.gridWidth.ReadOnly = true;
			this.gridWidth.Size = new System.Drawing.Size(81, 21);
			this.gridWidth.TabIndex = 6;
			this.gridWidth.Text = "0";
			// 
			// gridX
			// 
			this.gridX.Location = new System.Drawing.Point(76, 95);
			this.gridX.Name = "gridX";
			this.gridX.ReadOnly = true;
			this.gridX.Size = new System.Drawing.Size(81, 21);
			this.gridX.TabIndex = 6;
			this.gridX.Text = "0";
			// 
			// gridRows
			// 
			this.gridRows.Location = new System.Drawing.Point(76, 9);
			this.gridRows.Name = "gridRows";
			this.gridRows.Size = new System.Drawing.Size(100, 21);
			this.gridRows.TabIndex = 6;
			this.gridRows.Text = "2";
			this.gridRows.TextChanged += new System.EventHandler(this.gridRows_TextChanged);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(8, 40);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(49, 12);
			this.label5.TabIndex = 3;
			this.label5.Text = "Column";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(8, 173);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(37, 12);
			this.label7.TabIndex = 4;
			this.label7.Text = "Scale";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(8, 126);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(30, 12);
			this.label8.TabIndex = 4;
			this.label8.Text = "Size";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(8, 99);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(37, 12);
			this.label6.TabIndex = 4;
			this.label6.Text = "Begin";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(8, 13);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(30, 12);
			this.label4.TabIndex = 4;
			this.label4.Text = "Row";
			// 
			// panel13
			// 
			this.panel13.Controls.Add(this.buttonLoadSpriteSheet);
			this.panel13.Controls.Add(this.buttonSave);
			this.panel13.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel13.Location = new System.Drawing.Point(3, 539);
			this.panel13.Name = "panel13";
			this.panel13.Size = new System.Drawing.Size(1078, 91);
			this.panel13.TabIndex = 1;
			// 
			// buttonLoadSpriteSheet
			// 
			this.buttonLoadSpriteSheet.Location = new System.Drawing.Point(889, 63);
			this.buttonLoadSpriteSheet.Name = "buttonLoadSpriteSheet";
			this.buttonLoadSpriteSheet.Size = new System.Drawing.Size(103, 23);
			this.buttonLoadSpriteSheet.TabIndex = 0;
			this.buttonLoadSpriteSheet.Text = "Load Sprite";
			this.buttonLoadSpriteSheet.UseVisualStyleBackColor = true;
			this.buttonLoadSpriteSheet.Click += new System.EventHandler(this.buttonLoadSpriteSheet_Click);
			// 
			// buttonSave
			// 
			this.buttonSave.Location = new System.Drawing.Point(998, 63);
			this.buttonSave.Name = "buttonSave";
			this.buttonSave.Size = new System.Drawing.Size(75, 23);
			this.buttonSave.TabIndex = 0;
			this.buttonSave.Text = "Save";
			this.buttonSave.UseVisualStyleBackColor = true;
			this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(1092, 24);
			this.menuStrip1.TabIndex = 1;
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
			this.newToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
			this.newToolStripMenuItem.Text = "New";
			this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this.openToolStripMenuItem.Name = "openToolStripMenuItem";
			this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
			this.openToolStripMenuItem.Text = "Open";
			this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
			this.saveToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
			this.saveToolStripMenuItem.Text = "Save";
			this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
			this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
			this.saveAsToolStripMenuItem.Text = "Save as";
			this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
			// 
			// PBSpriteManager
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1092, 683);
			this.Controls.Add(this.tabControl1);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "PBSpriteManager";
			this.Text = "PBSprite Tool";
			this.tabControl1.ResumeLayout(false);
			this.spriteTab.ResumeLayout(false);
			this.mainSplitContainer.Panel1.ResumeLayout(false);
			this.mainSplitContainer.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).EndInit();
			this.mainSplitContainer.ResumeLayout(false);
			this.splitContainer2.Panel1.ResumeLayout(false);
			this.splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
			this.splitContainer2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.spriteGridView)).EndInit();
			this.panel2.ResumeLayout(false);
			this.panel9.ResumeLayout(false);
			this.panel9.PerformLayout();
			this.panel10.ResumeLayout(false);
			this.panel11.ResumeLayout(false);
			this.panel11.PerformLayout();
			this.panel4.ResumeLayout(false);
			this.panel4.PerformLayout();
			this.panel5.ResumeLayout(false);
			this.panel5.PerformLayout();
			this.panel6.ResumeLayout(false);
			this.panel6.PerformLayout();
			this.panel3.ResumeLayout(false);
			this.panel3.PerformLayout();
			this.panel7.ResumeLayout(false);
			this.panel7.PerformLayout();
			this.panel8.ResumeLayout(false);
			this.panel8.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.splitTab.ResumeLayout(false);
			this.panel12.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.panel14.ResumeLayout(false);
			this.panel14.PerformLayout();
			this.panel13.ResumeLayout(false);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage spriteTab;
        private System.Windows.Forms.TabPage splitTab;
        private System.Windows.Forms.SplitContainer mainSplitContainer;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.DataGridView spriteGridView;
        private System.Windows.Forms.DataGridViewTextBoxColumn spriteNameColumn;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.TextBox spriteSizeTextBox;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.TextBox spriteNameTextBox;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button loadSpriteButton;
        private System.Windows.Forms.Button applyButton;
        private System.Windows.Forms.Panel canvasPanel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
		private System.Windows.Forms.Panel panel9;
		private System.Windows.Forms.Panel panel10;
		private System.Windows.Forms.ComboBox pivots;
		private System.Windows.Forms.Panel panel11;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Panel panel12;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.Panel panel14;
		private System.Windows.Forms.TextBox gridColumns;
		private System.Windows.Forms.TextBox gridRows;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Panel panel13;
		private System.Windows.Forms.Button buttonLoadSpriteSheet;
		private System.Windows.Forms.Button buttonSave;
		private SpriteEditor.SpriteSheetPanel spriteSheetPanel;
		private System.Windows.Forms.CheckBox drawGrid;
		private System.Windows.Forms.TextBox gridHeight;
		private System.Windows.Forms.TextBox gridY;
		private System.Windows.Forms.TextBox gridWidth;
		private System.Windows.Forms.TextBox gridX;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox zoomScale;
		private System.Windows.Forms.Label label7;
	}
}

