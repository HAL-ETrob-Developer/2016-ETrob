namespace EV3RT_2016_FORM
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.createSW = new System.Windows.Forms.Button();
            this.nmTextBoxSpdP = new System.Windows.Forms.TextBox();
            this.nmTextBoxSpdI = new System.Windows.Forms.TextBox();
            this.nmTextBoxSpdD = new System.Windows.Forms.TextBox();
            this.nmTextBoxDegD = new System.Windows.Forms.TextBox();
            this.nmTextBoxDegI = new System.Windows.Forms.TextBox();
            this.nmTextBoxDegP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupSpd = new System.Windows.Forms.GroupBox();
            this.groupDeg = new System.Windows.Forms.GroupBox();
            this.righitStateDataGrid = new System.Windows.Forms.DataGridView();
            this.RIdxNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxNextCond = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.RIdxCoundValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxActNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RIdxNextNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupRighitIndex = new System.Windows.Forms.GroupBox();
            this.RIdxSortSw = new System.Windows.Forms.Button();
            this.groupLeftIndex = new System.Windows.Forms.GroupBox();
            this.LIdxSortSw = new System.Windows.Forms.Button();
            this.leftStateDataGrid = new System.Windows.Forms.DataGridView();
            this.LIdxNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxNextCond = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.LIdxCoundValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxActNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LIdxNextNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.loadSW = new System.Windows.Forms.Button();
            this.ev3OpenFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.groupRunningIndex = new System.Windows.Forms.GroupBox();
            this.runninngIndexGridView = new System.Windows.Forms.DataGridView();
            this.RunNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunSpeed = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunTrun = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunTailDeg = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunBalance = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.ControlLabel = new System.Windows.Forms.Label();
            this.groupTerget = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.nmTextBoxTerRefLV = new System.Windows.Forms.TextBox();
            this.nmTextBoxTerSpeed = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.scTextBoxTerRefLV = new System.Windows.Forms.TextBox();
            this.scTextBoxTerSpeed = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.scTextBoxDegD = new System.Windows.Forms.TextBox();
            this.scTextBoxDegI = new System.Windows.Forms.TextBox();
            this.scTextBoxDegP = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.scTextBoxSpdD = new System.Windows.Forms.TextBox();
            this.scTextBoxSpdI = new System.Windows.Forms.TextBox();
            this.scTextBoxSpdP = new System.Windows.Forms.TextBox();
            this.groupSpd.SuspendLayout();
            this.groupDeg.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.righitStateDataGrid)).BeginInit();
            this.groupRighitIndex.SuspendLayout();
            this.groupLeftIndex.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.leftStateDataGrid)).BeginInit();
            this.groupRunningIndex.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.runninngIndexGridView)).BeginInit();
            this.groupTerget.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // createSW
            // 
            this.createSW.Location = new System.Drawing.Point(919, 450);
            this.createSW.Name = "createSW";
            this.createSW.Size = new System.Drawing.Size(75, 23);
            this.createSW.TabIndex = 0;
            this.createSW.Text = "CREATE";
            this.createSW.UseVisualStyleBackColor = true;
            this.createSW.Click += new System.EventHandler(this.createSW_Click);
            // 
            // nmTextBoxSpdP
            // 
            this.nmTextBoxSpdP.Location = new System.Drawing.Point(43, 21);
            this.nmTextBoxSpdP.Name = "nmTextBoxSpdP";
            this.nmTextBoxSpdP.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxSpdP.TabIndex = 1;
            // 
            // nmTextBoxSpdI
            // 
            this.nmTextBoxSpdI.Location = new System.Drawing.Point(43, 52);
            this.nmTextBoxSpdI.Name = "nmTextBoxSpdI";
            this.nmTextBoxSpdI.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxSpdI.TabIndex = 2;
            // 
            // nmTextBoxSpdD
            // 
            this.nmTextBoxSpdD.Location = new System.Drawing.Point(43, 84);
            this.nmTextBoxSpdD.Name = "nmTextBoxSpdD";
            this.nmTextBoxSpdD.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxSpdD.TabIndex = 3;
            // 
            // nmTextBoxDegD
            // 
            this.nmTextBoxDegD.Location = new System.Drawing.Point(47, 84);
            this.nmTextBoxDegD.Name = "nmTextBoxDegD";
            this.nmTextBoxDegD.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxDegD.TabIndex = 6;
            // 
            // nmTextBoxDegI
            // 
            this.nmTextBoxDegI.Location = new System.Drawing.Point(47, 52);
            this.nmTextBoxDegI.Name = "nmTextBoxDegI";
            this.nmTextBoxDegI.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxDegI.TabIndex = 5;
            // 
            // nmTextBoxDegP
            // 
            this.nmTextBoxDegP.Location = new System.Drawing.Point(47, 21);
            this.nmTextBoxDegP.Name = "nmTextBoxDegP";
            this.nmTextBoxDegP.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxDegP.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(12, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "P";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 87);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "D";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(8, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "I";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(28, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(8, 12);
            this.label4.TabIndex = 12;
            this.label4.Text = "I";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(27, 87);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(13, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "D";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(27, 24);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(12, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "P";
            // 
            // groupSpd
            // 
            this.groupSpd.Controls.Add(this.label3);
            this.groupSpd.Controls.Add(this.label2);
            this.groupSpd.Controls.Add(this.label1);
            this.groupSpd.Controls.Add(this.nmTextBoxSpdD);
            this.groupSpd.Controls.Add(this.nmTextBoxSpdI);
            this.groupSpd.Controls.Add(this.nmTextBoxSpdP);
            this.groupSpd.Location = new System.Drawing.Point(46, 100);
            this.groupSpd.Name = "groupSpd";
            this.groupSpd.Size = new System.Drawing.Size(120, 116);
            this.groupSpd.TabIndex = 13;
            this.groupSpd.TabStop = false;
            this.groupSpd.Text = "SPEED";
            // 
            // groupDeg
            // 
            this.groupDeg.Controls.Add(this.label4);
            this.groupDeg.Controls.Add(this.label5);
            this.groupDeg.Controls.Add(this.label6);
            this.groupDeg.Controls.Add(this.nmTextBoxDegD);
            this.groupDeg.Controls.Add(this.nmTextBoxDegI);
            this.groupDeg.Controls.Add(this.nmTextBoxDegP);
            this.groupDeg.Location = new System.Drawing.Point(179, 100);
            this.groupDeg.Name = "groupDeg";
            this.groupDeg.Size = new System.Drawing.Size(120, 116);
            this.groupDeg.TabIndex = 14;
            this.groupDeg.TabStop = false;
            this.groupDeg.Text = "DEGREE";
            // 
            // righitStateDataGrid
            // 
            this.righitStateDataGrid.AllowDrop = true;
            this.righitStateDataGrid.AllowUserToAddRows = false;
            this.righitStateDataGrid.AllowUserToDeleteRows = false;
            this.righitStateDataGrid.AllowUserToResizeColumns = false;
            this.righitStateDataGrid.AllowUserToResizeRows = false;
            this.righitStateDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.righitStateDataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.RIdxNo,
            this.RIdxNextCond,
            this.RIdxCoundValue,
            this.RIdxActNo,
            this.RIdxNextNo});
            this.righitStateDataGrid.Location = new System.Drawing.Point(21, 23);
            this.righitStateDataGrid.Name = "righitStateDataGrid";
            this.righitStateDataGrid.RowTemplate.Height = 21;
            this.righitStateDataGrid.Size = new System.Drawing.Size(368, 150);
            this.righitStateDataGrid.TabIndex = 15;
            this.righitStateDataGrid.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.righitStateDataGrid_CellParsing);
            // 
            // RIdxNo
            // 
            this.RIdxNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            dataGridViewCellStyle2.Format = "0";
            dataGridViewCellStyle2.NullValue = "0";
            this.RIdxNo.DefaultCellStyle = dataGridViewCellStyle2;
            this.RIdxNo.HeaderText = "No";
            this.RIdxNo.Name = "RIdxNo";
            this.RIdxNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxNo.Width = 25;
            // 
            // RIdxNextCond
            // 
            this.RIdxNextCond.AutoComplete = false;
            this.RIdxNextCond.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.RIdxNextCond.HeaderText = "NextCond";
            this.RIdxNextCond.Name = "RIdxNextCond";
            // 
            // RIdxCoundValue
            // 
            this.RIdxCoundValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxCoundValue.HeaderText = "CoundValue";
            this.RIdxCoundValue.Name = "RIdxCoundValue";
            this.RIdxCoundValue.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxCoundValue.Width = 72;
            // 
            // RIdxActNo
            // 
            this.RIdxActNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxActNo.HeaderText = "ActNo";
            this.RIdxActNo.Name = "RIdxActNo";
            this.RIdxActNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxActNo.Width = 43;
            // 
            // RIdxNextNo
            // 
            this.RIdxNextNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RIdxNextNo.HeaderText = "NextNo";
            this.RIdxNextNo.Name = "RIdxNextNo";
            this.RIdxNextNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RIdxNextNo.Width = 49;
            // 
            // groupRighitIndex
            // 
            this.groupRighitIndex.Controls.Add(this.RIdxSortSw);
            this.groupRighitIndex.Controls.Add(this.righitStateDataGrid);
            this.groupRighitIndex.Location = new System.Drawing.Point(582, 12);
            this.groupRighitIndex.Name = "groupRighitIndex";
            this.groupRighitIndex.Size = new System.Drawing.Size(412, 208);
            this.groupRighitIndex.TabIndex = 16;
            this.groupRighitIndex.TabStop = false;
            this.groupRighitIndex.Text = "RIGHIT_INDEX";
            // 
            // RIdxSortSw
            // 
            this.RIdxSortSw.Location = new System.Drawing.Point(314, 179);
            this.RIdxSortSw.Name = "RIdxSortSw";
            this.RIdxSortSw.Size = new System.Drawing.Size(75, 23);
            this.RIdxSortSw.TabIndex = 16;
            this.RIdxSortSw.Text = "ReSORT";
            this.RIdxSortSw.UseVisualStyleBackColor = true;
            this.RIdxSortSw.Click += new System.EventHandler(this.RIdxSortSw_Click);
            // 
            // groupLeftIndex
            // 
            this.groupLeftIndex.Controls.Add(this.LIdxSortSw);
            this.groupLeftIndex.Controls.Add(this.leftStateDataGrid);
            this.groupLeftIndex.Location = new System.Drawing.Point(582, 230);
            this.groupLeftIndex.Name = "groupLeftIndex";
            this.groupLeftIndex.Size = new System.Drawing.Size(412, 208);
            this.groupLeftIndex.TabIndex = 17;
            this.groupLeftIndex.TabStop = false;
            this.groupLeftIndex.Text = "LEFT_INDEX";
            // 
            // LIdxSortSw
            // 
            this.LIdxSortSw.Location = new System.Drawing.Point(314, 179);
            this.LIdxSortSw.Name = "LIdxSortSw";
            this.LIdxSortSw.Size = new System.Drawing.Size(75, 23);
            this.LIdxSortSw.TabIndex = 17;
            this.LIdxSortSw.Text = "ReSORT";
            this.LIdxSortSw.UseVisualStyleBackColor = true;
            this.LIdxSortSw.Click += new System.EventHandler(this.LIdxSortSw_Click);
            // 
            // leftStateDataGrid
            // 
            this.leftStateDataGrid.AllowUserToAddRows = false;
            this.leftStateDataGrid.AllowUserToDeleteRows = false;
            this.leftStateDataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.leftStateDataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LIdxNo,
            this.LIdxNextCond,
            this.LIdxCoundValue,
            this.LIdxActNo,
            this.LIdxNextNo});
            this.leftStateDataGrid.Location = new System.Drawing.Point(21, 23);
            this.leftStateDataGrid.Name = "leftStateDataGrid";
            this.leftStateDataGrid.RowTemplate.Height = 21;
            this.leftStateDataGrid.Size = new System.Drawing.Size(368, 150);
            this.leftStateDataGrid.TabIndex = 15;
            this.leftStateDataGrid.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.leftStateDataGrid_CellParsing);
            // 
            // LIdxNo
            // 
            this.LIdxNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.LIdxNo.HeaderText = "No";
            this.LIdxNo.Name = "LIdxNo";
            this.LIdxNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxNo.Width = 25;
            // 
            // LIdxNextCond
            // 
            this.LIdxNextCond.AutoComplete = false;
            this.LIdxNextCond.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.LIdxNextCond.HeaderText = "NextCond";
            this.LIdxNextCond.Name = "LIdxNextCond";
            // 
            // LIdxCoundValue
            // 
            this.LIdxCoundValue.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxCoundValue.HeaderText = "CoundValue";
            this.LIdxCoundValue.Name = "LIdxCoundValue";
            this.LIdxCoundValue.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxCoundValue.Width = 72;
            // 
            // LIdxActNo
            // 
            this.LIdxActNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxActNo.HeaderText = "ActNo";
            this.LIdxActNo.Name = "LIdxActNo";
            this.LIdxActNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxActNo.Width = 43;
            // 
            // LIdxNextNo
            // 
            this.LIdxNextNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.LIdxNextNo.HeaderText = "NextNo";
            this.LIdxNextNo.Name = "LIdxNextNo";
            this.LIdxNextNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.LIdxNextNo.Width = 49;
            // 
            // loadSW
            // 
            this.loadSW.Location = new System.Drawing.Point(18, 454);
            this.loadSW.Name = "loadSW";
            this.loadSW.Size = new System.Drawing.Size(75, 23);
            this.loadSW.TabIndex = 18;
            this.loadSW.Text = "LOAD";
            this.loadSW.UseVisualStyleBackColor = true;
            this.loadSW.Click += new System.EventHandler(this.loadSW_Click);
            // 
            // ev3OpenFileDialog
            // 
            this.ev3OpenFileDialog.DefaultExt = "evs";
            this.ev3OpenFileDialog.Filter = "\"EV3設定ファイル (*.evs)|*.evs|すべてのファイル (*.*)|*.*\"";
            this.ev3OpenFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.ev3OpenFileDialog_FileOk);
            // 
            // groupRunningIndex
            // 
            this.groupRunningIndex.Controls.Add(this.runninngIndexGridView);
            this.groupRunningIndex.Location = new System.Drawing.Point(305, 12);
            this.groupRunningIndex.Name = "groupRunningIndex";
            this.groupRunningIndex.Size = new System.Drawing.Size(271, 426);
            this.groupRunningIndex.TabIndex = 19;
            this.groupRunningIndex.TabStop = false;
            this.groupRunningIndex.Text = "RUNNINNG_INDEX";
            // 
            // runninngIndexGridView
            // 
            this.runninngIndexGridView.AllowUserToAddRows = false;
            this.runninngIndexGridView.AllowUserToDeleteRows = false;
            this.runninngIndexGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.runninngIndexGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.RunNo,
            this.RunSpeed,
            this.RunTrun,
            this.RunTailDeg,
            this.RunBalance});
            this.runninngIndexGridView.Location = new System.Drawing.Point(16, 23);
            this.runninngIndexGridView.Name = "runninngIndexGridView";
            this.runninngIndexGridView.RowTemplate.Height = 21;
            this.runninngIndexGridView.Size = new System.Drawing.Size(240, 385);
            this.runninngIndexGridView.TabIndex = 0;
            this.runninngIndexGridView.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler(this.runninngIndexeDataGrid_CellParsing);
            // 
            // RunNo
            // 
            this.RunNo.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunNo.Frozen = true;
            this.RunNo.HeaderText = "No";
            this.RunNo.Name = "RunNo";
            this.RunNo.ReadOnly = true;
            this.RunNo.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunNo.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunNo.Width = 25;
            // 
            // RunSpeed
            // 
            this.RunSpeed.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunSpeed.HeaderText = "Speed";
            this.RunSpeed.Name = "RunSpeed";
            this.RunSpeed.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunSpeed.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunSpeed.Width = 42;
            // 
            // RunTrun
            // 
            this.RunTrun.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunTrun.HeaderText = "Trun";
            this.RunTrun.Name = "RunTrun";
            this.RunTrun.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunTrun.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunTrun.Width = 34;
            // 
            // RunTailDeg
            // 
            this.RunTailDeg.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.ColumnHeader;
            this.RunTailDeg.HeaderText = "Tail";
            this.RunTailDeg.Name = "RunTailDeg";
            this.RunTailDeg.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.RunTailDeg.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.RunTailDeg.Width = 30;
            // 
            // RunBalance
            // 
            this.RunBalance.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.RunBalance.HeaderText = "Balance";
            this.RunBalance.Name = "RunBalance";
            this.RunBalance.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // ControlLabel
            // 
            this.ControlLabel.AutoEllipsis = true;
            this.ControlLabel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ControlLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ControlLabel.Location = new System.Drawing.Point(216, 454);
            this.ControlLabel.Margin = new System.Windows.Forms.Padding(0);
            this.ControlLabel.MaximumSize = new System.Drawing.Size(800, 500);
            this.ControlLabel.Name = "ControlLabel";
            this.ControlLabel.Padding = new System.Windows.Forms.Padding(10, 5, 10, 3);
            this.ControlLabel.Size = new System.Drawing.Size(600, 22);
            this.ControlLabel.TabIndex = 20;
            this.ControlLabel.Text = "デバッグ：NULL";
            this.ControlLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupTerget
            // 
            this.groupTerget.Controls.Add(this.label7);
            this.groupTerget.Controls.Add(this.label9);
            this.groupTerget.Controls.Add(this.nmTextBoxTerRefLV);
            this.groupTerget.Controls.Add(this.nmTextBoxTerSpeed);
            this.groupTerget.Location = new System.Drawing.Point(46, 46);
            this.groupTerget.Name = "groupTerget";
            this.groupTerget.Size = new System.Drawing.Size(253, 43);
            this.groupTerget.TabIndex = 14;
            this.groupTerget.TabStop = false;
            this.groupTerget.Text = "TERGET";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(136, 22);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(37, 12);
            this.label7.TabIndex = 9;
            this.label7.Text = "RefLV";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(21, 22);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(36, 12);
            this.label9.TabIndex = 7;
            this.label9.Text = "Speed";
            // 
            // nmTextBoxTerRefLV
            // 
            this.nmTextBoxTerRefLV.Location = new System.Drawing.Point(180, 18);
            this.nmTextBoxTerRefLV.Name = "nmTextBoxTerRefLV";
            this.nmTextBoxTerRefLV.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxTerRefLV.TabIndex = 2;
            // 
            // nmTextBoxTerSpeed
            // 
            this.nmTextBoxTerSpeed.Location = new System.Drawing.Point(65, 18);
            this.nmTextBoxTerSpeed.Name = "nmTextBoxTerSpeed";
            this.nmTextBoxTerSpeed.Size = new System.Drawing.Size(55, 19);
            this.nmTextBoxTerSpeed.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label8.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.label8.Location = new System.Drawing.Point(16, 12);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(100, 23);
            this.label8.TabIndex = 21;
            this.label8.Text = "NormalMode";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label10
            // 
            this.label10.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label10.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.label10.Location = new System.Drawing.Point(16, 234);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(100, 23);
            this.label10.TabIndex = 25;
            this.label10.Text = "SearchMode";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.scTextBoxTerRefLV);
            this.groupBox1.Controls.Add(this.scTextBoxTerSpeed);
            this.groupBox1.Location = new System.Drawing.Point(46, 268);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(253, 43);
            this.groupBox1.TabIndex = 23;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "TERGET";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(136, 22);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(37, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "RefLV";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(21, 22);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(36, 12);
            this.label12.TabIndex = 7;
            this.label12.Text = "Speed";
            // 
            // scTextBoxTerRefLV
            // 
            this.scTextBoxTerRefLV.Location = new System.Drawing.Point(180, 18);
            this.scTextBoxTerRefLV.Name = "scTextBoxTerRefLV";
            this.scTextBoxTerRefLV.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxTerRefLV.TabIndex = 2;
            // 
            // scTextBoxTerSpeed
            // 
            this.scTextBoxTerSpeed.Location = new System.Drawing.Point(65, 18);
            this.scTextBoxTerSpeed.Name = "scTextBoxTerSpeed";
            this.scTextBoxTerSpeed.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxTerSpeed.TabIndex = 1;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label13);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.scTextBoxDegD);
            this.groupBox2.Controls.Add(this.scTextBoxDegI);
            this.groupBox2.Controls.Add(this.scTextBoxDegP);
            this.groupBox2.Location = new System.Drawing.Point(179, 322);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(120, 116);
            this.groupBox2.TabIndex = 24;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "DEGREE";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(28, 55);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(8, 12);
            this.label13.TabIndex = 12;
            this.label13.Text = "I";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(27, 87);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(13, 12);
            this.label14.TabIndex = 11;
            this.label14.Text = "D";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(27, 24);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(12, 12);
            this.label15.TabIndex = 10;
            this.label15.Text = "P";
            // 
            // scTextBoxDegD
            // 
            this.scTextBoxDegD.Location = new System.Drawing.Point(47, 84);
            this.scTextBoxDegD.Name = "scTextBoxDegD";
            this.scTextBoxDegD.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxDegD.TabIndex = 6;
            // 
            // scTextBoxDegI
            // 
            this.scTextBoxDegI.Location = new System.Drawing.Point(47, 52);
            this.scTextBoxDegI.Name = "scTextBoxDegI";
            this.scTextBoxDegI.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxDegI.TabIndex = 5;
            // 
            // scTextBoxDegP
            // 
            this.scTextBoxDegP.Location = new System.Drawing.Point(47, 21);
            this.scTextBoxDegP.Name = "scTextBoxDegP";
            this.scTextBoxDegP.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxDegP.TabIndex = 4;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label16);
            this.groupBox3.Controls.Add(this.label17);
            this.groupBox3.Controls.Add(this.label18);
            this.groupBox3.Controls.Add(this.scTextBoxSpdD);
            this.groupBox3.Controls.Add(this.scTextBoxSpdI);
            this.groupBox3.Controls.Add(this.scTextBoxSpdP);
            this.groupBox3.Location = new System.Drawing.Point(46, 322);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(120, 116);
            this.groupBox3.TabIndex = 22;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "SPEED";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(25, 56);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(8, 12);
            this.label16.TabIndex = 9;
            this.label16.Text = "I";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(24, 87);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(13, 12);
            this.label17.TabIndex = 8;
            this.label17.Text = "D";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(24, 25);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(12, 12);
            this.label18.TabIndex = 7;
            this.label18.Text = "P";
            // 
            // scTextBoxSpdD
            // 
            this.scTextBoxSpdD.Location = new System.Drawing.Point(43, 84);
            this.scTextBoxSpdD.Name = "scTextBoxSpdD";
            this.scTextBoxSpdD.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxSpdD.TabIndex = 3;
            // 
            // scTextBoxSpdI
            // 
            this.scTextBoxSpdI.Location = new System.Drawing.Point(43, 52);
            this.scTextBoxSpdI.Name = "scTextBoxSpdI";
            this.scTextBoxSpdI.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxSpdI.TabIndex = 2;
            // 
            // scTextBoxSpdP
            // 
            this.scTextBoxSpdP.Location = new System.Drawing.Point(43, 21);
            this.scTextBoxSpdP.Name = "scTextBoxSpdP";
            this.scTextBoxSpdP.Size = new System.Drawing.Size(55, 19);
            this.scTextBoxSpdP.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1006, 487);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.groupTerget);
            this.Controls.Add(this.ControlLabel);
            this.Controls.Add(this.groupRunningIndex);
            this.Controls.Add(this.loadSW);
            this.Controls.Add(this.groupLeftIndex);
            this.Controls.Add(this.groupRighitIndex);
            this.Controls.Add(this.groupDeg);
            this.Controls.Add(this.groupSpd);
            this.Controls.Add(this.createSW);
            this.Name = "Form1";
            this.Text = "EV3RT_FORM";
            this.groupSpd.ResumeLayout(false);
            this.groupSpd.PerformLayout();
            this.groupDeg.ResumeLayout(false);
            this.groupDeg.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.righitStateDataGrid)).EndInit();
            this.groupRighitIndex.ResumeLayout(false);
            this.groupLeftIndex.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.leftStateDataGrid)).EndInit();
            this.groupRunningIndex.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.runninngIndexGridView)).EndInit();
            this.groupTerget.ResumeLayout(false);
            this.groupTerget.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button createSW;
        private System.Windows.Forms.TextBox nmTextBoxSpdP;
        private System.Windows.Forms.TextBox nmTextBoxSpdI;
        private System.Windows.Forms.TextBox nmTextBoxSpdD;
        private System.Windows.Forms.TextBox nmTextBoxDegD;
        private System.Windows.Forms.TextBox nmTextBoxDegI;
        private System.Windows.Forms.TextBox nmTextBoxDegP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupSpd;
        private System.Windows.Forms.GroupBox groupDeg;
        private System.Windows.Forms.DataGridView righitStateDataGrid;
        private System.Windows.Forms.GroupBox groupRighitIndex;
        private System.Windows.Forms.GroupBox groupLeftIndex;
        private System.Windows.Forms.DataGridView leftStateDataGrid;
        private System.Windows.Forms.Button RIdxSortSw;
        private System.Windows.Forms.Button LIdxSortSw;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxNo;
        private System.Windows.Forms.DataGridViewComboBoxColumn LIdxNextCond;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxCoundValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxActNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn LIdxNextNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxNo;
        private System.Windows.Forms.DataGridViewComboBoxColumn RIdxNextCond;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxCoundValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxActNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RIdxNextNo;
        private System.Windows.Forms.Button loadSW;
        private System.Windows.Forms.OpenFileDialog ev3OpenFileDialog;
        private System.Windows.Forms.GroupBox groupRunningIndex;
        private System.Windows.Forms.DataGridView runninngIndexGridView;
        private System.Windows.Forms.Label ControlLabel;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunSpeed;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunTrun;
        private System.Windows.Forms.DataGridViewTextBoxColumn RunTailDeg;
        private System.Windows.Forms.DataGridViewCheckBoxColumn RunBalance;
        private System.Windows.Forms.GroupBox groupTerget;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox nmTextBoxTerRefLV;
        private System.Windows.Forms.TextBox nmTextBoxTerSpeed;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox scTextBoxTerRefLV;
        private System.Windows.Forms.TextBox scTextBoxTerSpeed;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox scTextBoxDegD;
        private System.Windows.Forms.TextBox scTextBoxDegI;
        private System.Windows.Forms.TextBox scTextBoxDegP;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox scTextBoxSpdD;
        private System.Windows.Forms.TextBox scTextBoxSpdI;
        private System.Windows.Forms.TextBox scTextBoxSpdP;
    }
}

