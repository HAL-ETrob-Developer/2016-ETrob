using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace EV3RT_2016_FORM
{
    public partial class Form1 : Form
    {
        /* 定数定義 ----------------------------------------------------------- */
        public const byte RIGHIT_INDEX_NUM = 50;
        public const byte LEFT_INDEX_NUM = RIGHIT_INDEX_NUM;
        public const byte RUNNING_INDEX_NUM = 20;

        public const byte SC_CLM___NO = 0;
        public const byte SC_CLM_NXCD = 1;
        public const byte SC_CLM_CDVL = 2;
        public const byte SC_CLM_ACTN = 3;
        public const byte SC_CLM_NXNO = 4;

        public const byte RUN_CLM__NO = 0;
        public const byte RUN_CLM_SPD = 1;
        public const byte RUN_CLM_TRN = 2;
        public const byte RUN_CLM_T_D = 3;
        public const byte RUN_CLM_BLN = 4;

        public const byte INDEX_MULTI = 10;
        public const byte INDEX_R_ADD = 1;
        public const byte INDEX_L_ADD = 51;

        public const string _CLS_BLK = "CLS_BLK";
        public const string _CLS_GRY = "CLS_GRY";
        public const string _CLS_WHT = "CLS_WHT";
        public const string _RUN_MLG = "RUN_MLG";
        public const string _EV3_DEG = "EV3_DEG";
        public const string _TIL_DEG = "TIL_DEG";
        public const string _GYR__ST = "GYR__ST";
        public const string _GYR_UST = "GYR_UST";
        public const string _EX_SLIP = "EX_SLIP";
        public const string _EX_END  = "EX_END";

        public string[] NEXT_COUND_STR = {  _CLS_BLK,
                                            _CLS_GRY,
                                            _CLS_WHT,
                                            _RUN_MLG,
                                            _EV3_DEG,
                                            _TIL_DEG,
                                            _GYR__ST,
                                            _GYR_UST,
                                            _EX_SLIP,
                                            _EX_END };
        /* イニシャライズ ----------------------------------------------------------- */
        public Form1()
        {
            InitializeComponent();
            gainsTextBox_init();
            righitStateDataGrid_init();
            leftStateDataGrid_init();
            runninngIndexGridView_init();

            ControlLabel.Text = "初期化終了";
        }

        /* ゲイン */
        private void gainsTextBox_init()//new20160811
        {
            textBoxSpdP.Text = "0.008";
            textBoxSpdI.Text = "0.001";
            textBoxSpdD.Text = "0.004";
            textBoxDegP.Text = "0.2";
            textBoxDegI.Text = "0.1";
            textBoxDegD.Text = "15.0";
        }
        /* 右コースシナリオ */
        private void righitStateDataGrid_init()
        {
            //入力規則
            for (int i = 0; ; i++)
            {
                try
                {
                    RIdxNextCond.Items.Add(NEXT_COUND_STR[i]);
                }
                catch (IndexOutOfRangeException)
                {
                    break;
                }
            }
            //行の生成
            for (int iNo = 0; iNo < RIGHIT_INDEX_NUM; iNo++)
            {
                this.righitStateDataGrid.Rows.Add();
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM___NO].Value = iNo * INDEX_MULTI;
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM_NXCD].Value = _EX_SLIP;
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM_CDVL].Value = 0;
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM_ACTN].Value = 0;
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM_NXNO].Value = iNo + INDEX_R_ADD;
            }
        }
        /* 左コースシナリオ */
        private void leftStateDataGrid_init()
        {
            //入力規則
            for (int i = 0; ; i++)
            {
                try
                {
                    LIdxNextCond.Items.Add(NEXT_COUND_STR[i]);
                }
                catch (IndexOutOfRangeException)
                {
                    break;
                }
            }
            //行の生成
            for (int iNo = 0; iNo < LEFT_INDEX_NUM; iNo++)
            {
                this.leftStateDataGrid.Rows.Add();
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM___NO].Value = iNo * INDEX_MULTI;
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM_NXCD].Value = _EX_SLIP;
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM_CDVL].Value = 0;
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM_ACTN].Value = 0;
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM_NXNO].Value = iNo + INDEX_L_ADD;
            }
        }
        /* 走行インデックス */
        private void runninngIndexGridView_init()
        {
            //行の生成
            for (int iNo = 0; iNo < RUNNING_INDEX_NUM; iNo++)
            {
                this.runninngIndexGridView.Rows.Add();
                this.runninngIndexGridView.Rows[iNo].Cells[RUN_CLM__NO].Value = iNo;
                this.runninngIndexGridView.Rows[iNo].Cells[RUN_CLM_SPD].Value = 50;
                this.runninngIndexGridView.Rows[iNo].Cells[RUN_CLM_TRN].Value = 0;
                this.runninngIndexGridView.Rows[iNo].Cells[RUN_CLM_T_D].Value = 0;
                this.runninngIndexGridView.Rows[iNo].Cells[RUN_CLM_BLN].Value = true;
            }
        }

        /* DataGrid値変換 ----------------------------------------------------------- */
        //右コース
        private void righitStateDataGrid_CellParsing(object sender, DataGridViewCellParsingEventArgs e )
        {
            DataGridView TempDgv = (DataGridView)sender;
            //セルの列と型を調べる
            if (TempDgv.Columns[e.ColumnIndex].Name != "RIdxNextCond" ) {
                if((string)e.Value != "" ) {
                    //数値化した値をセルの値とする
                    e.Value = int.Parse((string)e.Value);
                } else {
                    e.Value = 0;
                }

                //解析が不要であることを知らせる
                e.ParsingApplied = true;
            }
        }

        //左コース
        private void leftStateDataGrid_CellParsing(object sender, DataGridViewCellParsingEventArgs e )
        {
            DataGridView TempDgv = (DataGridView)sender;
            //セルの列と型を調べる
            if (TempDgv.Columns[e.ColumnIndex].Name != "LIdxNextCond" ) {
                if((string)e.Value != "" ) {
                    //数値化した値をセルの値とする
                    e.Value = int.Parse((string)e.Value);
                } else {
                    e.Value = 0;
                }

                //解析が不要であることを知らせる
                e.ParsingApplied = true;
            }
        }

        //走行インデックス
        private void runninngIndexeDataGrid_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
        {
            DataGridView TempDgv = (DataGridView)sender;
            //セルの列と型を調べる
            if (TempDgv.Columns[e.ColumnIndex].Name != "RunBalance")
            {
                if ((string)e.Value != "")
                {
                    //数値化した値をセルの値とする
                    e.Value = int.Parse((string)e.Value);
                }
                else
                {
                    e.Value = 0;
                }

                //解析が不要であることを知らせる
                e.ParsingApplied = true;
            }
        }

        /* 再ソート処理 ----------------------------------------------------------- */
        //右コース
        private void RIdxSortSw_Click(object sender, EventArgs e)
        {
            //並び替える列を決める
            DataGridViewColumn sortColumn = righitStateDataGrid.Columns[SC_CLM___NO];

            //並び替えの方向（昇順か降順か）を決める
            ListSortDirection sortDirection = ListSortDirection.Ascending;

            //並び替えを行う
            righitStateDataGrid.Sort(sortColumn, sortDirection);

            //行番号の再生成
            for (int iNo = 0; iNo < RIGHIT_INDEX_NUM; iNo++)
            {
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM___NO].Value = iNo * INDEX_MULTI;
                this.righitStateDataGrid.Rows[iNo].Cells[SC_CLM_NXNO].Value = iNo + INDEX_R_ADD;
            }
        }
        //左コース
        private void LIdxSortSw_Click(object sender, EventArgs e)
        {
            //並び替える列を決める
            DataGridViewColumn sortColumn = leftStateDataGrid.Columns[SC_CLM___NO];

            //並び替えの方向（昇順か降順か）を決める
            ListSortDirection sortDirection = ListSortDirection.Ascending;

            //並び替えを行う
            leftStateDataGrid.Sort(sortColumn, sortDirection);

            //行番号の再生成
            for (int iNo = 0; iNo < RIGHIT_INDEX_NUM; iNo++)
            {
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM___NO].Value = iNo * INDEX_MULTI;
                this.leftStateDataGrid.Rows[iNo].Cells[SC_CLM_NXNO].Value = iNo + INDEX_R_ADD;
            }
        }

        /* 設定ファイル生成 ----------------------------------------------------------- */
        private void createSW_Click(object sender, EventArgs e)
        {
            EV3_SETTING setingF;
            setingF.righitScen = new SCENARIO[RIGHIT_INDEX_NUM];
            setingF.leftScen   = new SCENARIO[LEFT_INDEX_NUM];
            setingF.runState   = new RUN_STATE[RUNNING_INDEX_NUM];

            ControlLabel.Text = "設定ファイルの生成を開始";

            /* PIDゲイン値の取得 */
            setingF.pidGains = getPidGains();
            /* 右シナリオの取得 */
            setingF.righitScen = getScenario(this.righitStateDataGrid);
            /* 左シナリオの取得 */
            setingF.leftScen = getScenario(this.leftStateDataGrid);
            /* 走行インデックスの取得 */
            setingF.runState = getRunningState(this.runninngIndexGridView);

            // バイナリ形式でファイルに書き出し。
            using (BinaryWriter w = new BinaryWriter(File.Create(@"ev3_settings.evs")))
            {
                //PIDゲイン値の書き込み
                w.Write(setingF.pidGains.fSpdP);
                w.Write(setingF.pidGains.fSpdI);
                w.Write(setingF.pidGains.fSpdD);
                w.Write(setingF.pidGains.fDegP);
                w.Write(setingF.pidGains.fDegI);
                w.Write(setingF.pidGains.fDegD);

                //右シナリオの書き込み
                for (int i = 0; ; i++)
                {
                    try
                    {
                        w.Write(setingF.righitScen[i].nextCond);
                        w.Write(setingF.righitScen[i].actNo);
                        w.Write(setingF.righitScen[i].nextNo);
                        w.Write(setingF.righitScen[i].dummy);
                        w.Write(setingF.righitScen[i].coundValue);
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                }

                //左シナリオの書き込み
                for (int i = 0; ; i++)
                {
                    try
                    {
                        w.Write(setingF.leftScen[i].nextCond);
                        w.Write(setingF.leftScen[i].actNo);
                        w.Write(setingF.leftScen[i].nextNo);
                        w.Write(setingF.leftScen[i].dummy);
                        w.Write(setingF.leftScen[i].coundValue);
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                }

                //走行インデックスの書き込み
                for (int i = 0; ; i++)
                {
                    try
                    {
                        w.Write(setingF.runState[i].speed);
                        w.Write(setingF.runState[i].turn);
                        w.Write(setingF.runState[i].tailDeg);
                        w.Write(setingF.runState[i].balance);
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                }
            }
            //設定ファイル生成後に終了
            ControlLabel.Text = "設定ファイルの生成を終了";
            //this.Close();
        }
        /* PIDゲイン値の抽出 */
        private PID_SETTING getPidGains()
        {
            string strSpdP = textBoxSpdP.Text;
            string strSpdI = textBoxSpdI.Text;
            string strSpdD = textBoxSpdD.Text;
            string strDegP = textBoxDegP.Text;
            string strDegI = textBoxDegI.Text;
            string strDegD = textBoxDegD.Text;

            PID_SETTING pidSetFile;
            pidSetFile.fSpdP = 0.0F;
            pidSetFile.fSpdI = 0.0F;
            pidSetFile.fSpdD = 0.0F;
            pidSetFile.fDegP = 0.0F;
            pidSetFile.fDegI = 0.0F;
            pidSetFile.fDegD = 0.0F;

            if (strSpdP != "") { pidSetFile.fSpdP = float.Parse(strSpdP); }
            if (strSpdI != "") { pidSetFile.fSpdI = float.Parse(strSpdI); }
            if (strSpdD != "") { pidSetFile.fSpdD = float.Parse(strSpdD); }
            if (strDegP != "") { pidSetFile.fDegP = float.Parse(strDegP); }
            if (strDegI != "") { pidSetFile.fDegI = float.Parse(strDegI); }
            if (strDegD != "") { pidSetFile.fDegD = float.Parse(strDegD); }

            return pidSetFile;
        }
        /* シナリオ値の抽出 */
        private SCENARIO[] getScenario( object dataGrid )
        {
            SCENARIO[] ThisScens = new SCENARIO[RIGHIT_INDEX_NUM];
            DataGridView ThisGridView = (DataGridView)dataGrid;
            byte CheckNexCd = 0;

            //checkNexCdを_EX_SLIPの番号にセット
            while( NEXT_COUND_STR[CheckNexCd] != _EX_SLIP ) { CheckNexCd++; }

            for (int i = 0; ;i++)
            {
                try
                {
                    ThisScens[i].nextCond = CheckNexCd;//_EX_SLIPの番号
                    ThisScens[i].actNo    = 0;
                    ThisScens[i].nextNo   = 0;
                    ThisScens[i].coundValue = 0;
                    ThisScens[i].dummy    = 0;
                }
                catch( IndexOutOfRangeException )
                {
                    break;
                }
            }

            for (int i = 0; ; i++)
            {
                try
                {
                    ThisScens[i].actNo = (byte)(int)(ThisGridView.Rows[i].Cells[SC_CLM_ACTN].Value);
                    ThisScens[i].nextNo = (byte)(int)(ThisGridView.Rows[i].Cells[SC_CLM_NXNO].Value);
                    ThisScens[i].coundValue = (Int32)(ThisGridView.Rows[i].Cells[SC_CLM_CDVL].Value);

                    //nextCondサーチ
                    for (CheckNexCd = 0; ; CheckNexCd++)
                    {
                        if (( string )ThisGridView.Rows[i].Cells[SC_CLM_NXCD].Value == NEXT_COUND_STR[CheckNexCd]) { break; }
                    }

                    ThisScens[i].nextCond   = CheckNexCd;
                }
                catch (IndexOutOfRangeException)
                {
                    break;
                }
            }

            return ThisScens;
        }
        /* 走行インデックスの抽出 */
        private RUN_STATE[] getRunningState(object dataGrid)
        {
            RUN_STATE[] ThisRunSta = new RUN_STATE[RUNNING_INDEX_NUM];
            DataGridView ThisGridView = (DataGridView)dataGrid;

            for (int i = 0; ; i++)
            {
                try
                {
                    ThisRunSta[i].speed = 50;
                    ThisRunSta[i].turn  = 0;
                    ThisRunSta[i].tailDeg = 0;
                    ThisRunSta[i].balance = 0;
                }
                catch (IndexOutOfRangeException)
                {
                    break;
                }
            }

            for (int i = 0; ; i++)
            {
                try
                {
                    ThisRunSta[i].speed   = (sbyte)(int)(ThisGridView.Rows[i].Cells[RUN_CLM_SPD].Value);
                    ThisRunSta[i].turn    = (sbyte)(int)(ThisGridView.Rows[i].Cells[RUN_CLM_TRN].Value);
                    ThisRunSta[i].tailDeg = (sbyte)(int)(ThisGridView.Rows[i].Cells[RUN_CLM_T_D].Value);
                    if((bool)ThisGridView.Rows[i].Cells[RUN_CLM_BLN].Value ) { ThisRunSta[i].balance = 1; }
                }
                catch (IndexOutOfRangeException)
                {
                    break;
                }
            }

            return ThisRunSta;
        }


        /* 設定ファイルの取得 ----------------------------------------------------------- */
        /* オープンファイルダイアログの表示 */
        private void loadSW_Click(object sender, EventArgs e)
        {
            ControlLabel.Text = "設定ファイルのロード";
            ev3OpenFileDialog.ShowDialog();
        }
        /* 設定ファイル展開 */
        private void ev3OpenFileDialog_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            OpenFileDialog ThisOFD = (OpenFileDialog)sender;

            ControlLabel.Text = "設定ファイルの読み込み開始";

            //OKボタンがクリックされたとき、選択されたファイルを読み取り専用で開く
            using (System.IO.Stream stream = ThisOFD.OpenFile())
            using (BinaryReader w = new BinaryReader(stream))
            {
                for (int getByte = 0; ; getByte++) {
                    try
                    {
                        //PIDゲイン値の読み込み
                        textBoxSpdP.Text = w.ReadSingle().ToString();
                        textBoxSpdI.Text = w.ReadSingle().ToString();
                        textBoxSpdD.Text = w.ReadSingle().ToString();
                        textBoxDegP.Text = w.ReadSingle().ToString();
                        textBoxDegI.Text = w.ReadSingle().ToString();
                        textBoxDegD.Text = w.ReadSingle().ToString();
                        //右シナリオ値の読み込み
                        for (int i = 0; i < RIGHIT_INDEX_NUM; i++)
                        {
                            righitStateDataGrid.Rows[i].Cells[SC_CLM_NXCD].Value = NEXT_COUND_STR[w.ReadByte()];
                            righitStateDataGrid.Rows[i].Cells[SC_CLM_ACTN].Value = (int)w.ReadByte();
                            righitStateDataGrid.Rows[i].Cells[SC_CLM_NXNO].Value = (int)w.ReadByte();
                            w.ReadByte();
                            righitStateDataGrid.Rows[i].Cells[SC_CLM_CDVL].Value = (int)w.ReadInt32();
                        }
                        //左シナリオ値の読み込み
                        for (int i = 0; i < LEFT_INDEX_NUM; i++)
                        {
                            leftStateDataGrid.Rows[i].Cells[SC_CLM_NXCD].Value = NEXT_COUND_STR[w.ReadByte()];
                            leftStateDataGrid.Rows[i].Cells[SC_CLM_ACTN].Value = (int)w.ReadByte();
                            leftStateDataGrid.Rows[i].Cells[SC_CLM_NXNO].Value = (int)w.ReadByte();
                            w.ReadByte();
                            leftStateDataGrid.Rows[i].Cells[SC_CLM_CDVL].Value = (int)w.ReadInt32();
                        }
                        //走行インデックス値の読み込み
                        for (int i = 0; i < RUNNING_INDEX_NUM; i++)
                        {
                            runninngIndexGridView.Rows[i].Cells[RUN_CLM_SPD].Value = (int)(sbyte)w.ReadByte();
                            runninngIndexGridView.Rows[i].Cells[RUN_CLM_TRN].Value = (int)(sbyte)w.ReadByte();
                            runninngIndexGridView.Rows[i].Cells[RUN_CLM_T_D].Value = (int)(sbyte)w.ReadByte();
                            if (w.ReadByte() == 1) {
                                runninngIndexGridView.Rows[i].Cells[RUN_CLM_BLN].Value = true;
                            } else {
                                runninngIndexGridView.Rows[i].Cells[RUN_CLM_BLN].Value = false;
                            }
                        }
                        break;
                    }
                    catch (EndOfStreamException)
                    {
                        break;
                    }
                    catch (IndexOutOfRangeException)
                    {
                        break;
                    }
                }

                ControlLabel.Text = "設定ファイルの読み込み完了";
            }
        }


        /* 構造体宣言 */
        struct EV3_SETTING {
            public PID_SETTING pidGains;
            public SCENARIO[]  righitScen;
            public SCENARIO[]  leftScen;
            public RUN_STATE[] runState;
        };

        struct RUN_STATE
        {
            public sbyte speed;
            public sbyte turn;
            public sbyte tailDeg;
            public byte balance;
        };

        struct SCENARIO {
            public byte  nextCond;
            public byte  actNo;
            public byte  nextNo;
            public byte  dummy;
            public Int32 coundValue;
        };

        struct PID_SETTING {
            public float fSpdP;
            public float fSpdI;
            public float fSpdD;
            public float fDegP;
            public float fDegI;
            public float fDegD;
        };

    }

}
