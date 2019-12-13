using OpenCvSharp;
using OpenCvSharp.Extensions;
using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace SpriteEditor
{
	public class SpriteSheetPanel : Panel
	{
		public delegate void GridSizeChangedHandler(object sender, Rectangle area);
		public event GridSizeChangedHandler GridSizeChanged;

		public delegate void ScaleChangedHandler(object sender, float scale);
		public event ScaleChangedHandler ScaleChanged;

		private bool _offsetDragging = false;
		private System.Drawing.Point _offsetBegin;

		private bool _gridDragging = false;
		private System.Drawing.Point _gridBegin;
		private System.Drawing.Point _gridLocation;
		public System.Drawing.Point GridLocation
		{
			get
			{
				var x = this._gridSize.Width  < 0 ? this._gridLocation.X - (int)this.GridSize.Width  : this._gridLocation.X;
				var y = this._gridSize.Height < 0 ? this._gridLocation.Y - (int)this.GridSize.Height : this._gridLocation.Y;

				return new System.Drawing.Point(x, y);
			}
		}

		private System.Drawing.SizeF _gridSize;
		public System.Drawing.SizeF GridSize
		{
			get
			{
				return new SizeF(Math.Abs(this._gridSize.Width), Math.Abs(this._gridSize.Height));
			}
		}

		public bool DrawGrid { get; set; }

		private int _rows, _columns;
		public int Rows
		{
			get
			{
				return this._rows;
			}
			set
			{
				this._rows = Math.Max(0, value);
				this.Invalidate();
			}
		}

		public int Columns
		{
			get
			{
				return this._columns;
			}
			set
			{
				this._columns = Math.Max(0, value);
				this.Invalidate();
			}
		}

		private float _scale;
		public float Scale
		{
			get
			{
				return this._scale;
			}
			set
			{
				this._scale = value;
				this._scale = Math.Max(0.1f, this._scale);
				this._scale = Math.Min(10, this._scale);

				this.ScaleChanged?.Invoke(this, this.Scale);
			}
		}

		private Mat _source;
		public Mat Source
		{
			get
			{
				return this._source;
			}
			set
			{
				this._source = value;
				if (this._source != null)
					this.SpriteSheet = BitmapConverter.ToBitmap(this._source);
			}
		}

		private Bitmap _spriteSheet;
		public Bitmap SpriteSheet
		{
			get
			{
				return this._spriteSheet;
			}
			private set
			{
				this._spriteSheet = value;
				this.Invalidate();
			}
		}

		public System.Drawing.Size DrawSize
		{
			get
			{
				return new System.Drawing.Size((int)(this.Source.Width * this.Scale), (int)(this.Source.Height * this.Scale));
			}
		}

		private System.Drawing.Point _offset;
		public System.Drawing.Point Offset
		{
			get
			{
				var drawSize = this.DrawSize;
				var ret = new System.Drawing.Point();

				if (DrawSize.Width < this.Width)
					ret.X = (int)((this.Width - drawSize.Width) / 2.0f);
				else
					ret.X = Math.Max(Math.Min(0, this._offset.X), this.Width - drawSize.Width);

				if (DrawSize.Height < this.Height)
					ret.Y = (int)((this.Height - drawSize.Height) / 2.0f);
				else
					ret.Y = Math.Max(Math.Min(0, this._offset.Y), this.Height - drawSize.Height);

				return ret;
			}
			private set
			{
				this._offset = value;
			}
		}

		public SpriteSheetPanel()
		{
			this.DoubleBuffered = true;
			this.Paint += this.SpriteSheetPanel_Paint;
			this.MouseWheel += this.SpriteSheetPanel_MouseWheel;
			this.MouseDown += this.SpriteSheetPanel_MouseDown;
			this.MouseUp += this.SpriteSheetPanel_MouseUp;
			this.MouseMove += this.SpriteSheetPanel_MouseMove;
		}

		private void SpriteSheetPanel_MouseMove(object sender, MouseEventArgs e)
		{
			if (this._offsetDragging)
			{
				var moved = new System.Drawing.Point(e.X - this._offsetBegin.X, e.Y - this._offsetBegin.Y);
				this.Offset = new System.Drawing.Point(this.Offset.X + moved.X, this.Offset.Y + moved.Y);
				this._offsetBegin = e.Location;
			}
			else if (this._gridDragging)
			{
				var moved = new System.Drawing.Point(e.X - this._gridBegin.X, e.Y - this._gridBegin.Y);
				this._gridSize = new System.Drawing.SizeF(this._gridSize.Width + moved.X / this.Scale, this._gridSize.Height + moved.Y / this.Scale);
				this._gridBegin = e.Location;

				this.GridSizeChanged?.Invoke(this, new Rectangle(this.GridLocation, new System.Drawing.Size((int)this.GridSize.Width, (int)this.GridSize.Height)));
			}
			
			this.Invalidate();
		}

		private void SpriteSheetPanel_MouseUp(object sender, MouseEventArgs e)
		{
			if (this.DrawGrid)
				this._gridDragging = false;
			else
				this._offsetDragging = false;
		}

		private void SpriteSheetPanel_MouseDown(object sender, MouseEventArgs e)
		{
			if (this.DrawGrid)
			{
				this._gridDragging = true;
				this._gridBegin = e.Location;
				this._gridLocation = new System.Drawing.Point((int)((e.X - this.Offset.X) / this.Scale), (int)((e.Y - this.Offset.Y) / this.Scale));
				this._gridSize = new System.Drawing.Size();
			}
			else
			{
				this._offsetDragging = true;
				this._offsetBegin = e.Location;
			}
		}

		private void SpriteSheetPanel_MouseWheel(object sender, MouseEventArgs e)
		{
			this.Scale += (e.Delta / 1200.0f);
			this.Invalidate();
		}

		private void SpriteSheetPanel_Paint(object sender, PaintEventArgs e)
		{
			if (this.SpriteSheet == null)
				return;

			e.Graphics.DrawImage(this.SpriteSheet, new Rectangle(this.Offset, this.DrawSize));

			var gridLocation = new System.Drawing.Point((int)(this.Scale * this.GridLocation.X + this.Offset.X), (int)(this.Scale * this.GridLocation.Y + this.Offset.Y));
			var gridSize = new System.Drawing.Size((int)(this.Scale * this.GridSize.Width), (int)(this.Scale * this.GridSize.Height));

			if (this.Columns > 0 && this.Rows > 0)
			{
				var between = new System.Drawing.Size(gridSize.Width / this.Columns, gridSize.Height / this.Rows);
				var limitWidth = (gridSize.Width / this.Columns) * this.Columns;
				for (var i = 0; i < this.Columns + 1; i++)
					e.Graphics.DrawLine(Pens.Black, new System.Drawing.Point(i * between.Width + gridLocation.X, gridLocation.Y), new System.Drawing.Point(i * between.Width + gridLocation.X, gridLocation.Y + gridSize.Height));

				for (var i = 0; i < this.Rows + 1; i++)
					e.Graphics.DrawLine(Pens.Black, new System.Drawing.Point(gridLocation.X, i * between.Height + gridLocation.Y), new System.Drawing.Point(gridLocation.X + limitWidth, i * between.Height + gridLocation.Y));
			}
		}

		public bool save(string path)
		{
			if (this.Rows == 0 || this.Columns == 0)
				return false;

			var between = new System.Drawing.Size((int)(this.GridSize.Width / this.Columns), (int)(this.GridSize.Height / this.Rows));
			for (var col = 0; col < this.Columns; col++)
			{
				for (var row = 0; row < this.Rows; row++)
				{
					var crop = this.Source[row * between.Height + this.GridLocation.Y, row * between.Height + this.GridLocation.Y + between.Height,
						col * between.Width + this.GridLocation.X, col * between.Width + this.GridLocation.X + between.Width];


					var trimed = TrimAlpha(crop);
					if (trimed != null && trimed.Width != 0 && trimed.Height != 0)
					{
						var destFileName = string.Format("{0}_{1}.png", Path.GetFileNameWithoutExtension(path), row * this.Columns + col);
						var fullFileName = Path.Combine(Path.GetDirectoryName(path), destFileName);
						trimed.ImWrite(fullFileName);
					}
				}
			}

			return true;
		}

		private Mat TrimAlpha(Mat source)
		{
			try
			{
				var alpha = source.ExtractChannel(3).FindNonZero();
				var splited = alpha.Split();

				double minX, maxX;
				splited[0].MinMaxIdx(out minX, out maxX);

				double minY, maxY;
				splited[1].MinMaxIdx(out minY, out maxY);

				return source[(int)minY, (int)maxY, (int)minX, (int)maxX];
			}
			catch (Exception)
			{
				return null;
			}
		}
	}
}