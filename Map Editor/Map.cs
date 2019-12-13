using SpriteEditor;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;

namespace MapEditor
{
	public class Map
	{
		public struct Tile
		{
			public enum Flag
			{
				Left = 0x00000001,
				Right = 0x00000002,
				Top = 0x00000004,
				Bottom = 0x00000008,
			}

			public byte id;
			public byte flag;

			public Tile(byte id, byte flag)
			{
				this.id = id;
				this.flag = flag;
			}
		}

		public class Enemy
		{
			public string name;
			public Point point;

			public Enemy(string name, Point point)
			{
				this.point = point;
				this.name = name;
			}
		}

		public List<Enemy> Enemies { get; private set; }
		public Nullable<Point>[] RespawnPoints { get; private set; }
		public int RespawnPointCount
		{
			get
			{
				var count = 0;
				foreach (var respawnPoint in this.RespawnPoints)
				{
					if (respawnPoint == null)
						continue;

					count++;
				}

				return count;
			}
		}

		//private string[,] _tiles;

		private Nullable<Tile>[,] _tiles;

		public string BGMName { get; private set; }
		public int Rows { get; private set; }
		public int Columns { get; private set; }

		public Size TileSize { get; private set; }

		public Sprite Sprite { get; private set; }

		public Map(string bgmName, int rows, int cols, int tWidth, int tHeight, Sprite sprite)
		{
			this.BGMName = bgmName;
			this.Sprite = sprite;
			this.Rows = rows;
			this.Columns = cols;
			this.TileSize = new Size(tWidth, tHeight);
			this._tiles = new Nullable<Tile>[this.Rows, this.Columns];

			this.Enemies = new List<Enemy>();
			this.RespawnPoints = new Nullable<Point>[8];
		}

		public Map(string filename, Sprite sprite)
		{
			this.Enemies = new List<Enemy>();
			this.RespawnPoints = new Nullable<Point>[8];

			if (this.load(filename, sprite) == false)
				throw new FileNotFoundException();
		}

		public Nullable<Tile> this[int row, int col]
		{
			get
			{
				return this._tiles[row, col];
			}
			set
			{
				this._tiles[row, col] = value;
			}
		}

		public bool load(string filename, Sprite sprite)
		{
			try
			{
				using (var reader = new BinaryReader(File.Open(filename, FileMode.Open)))
				{
					this.BGMName = reader.ReadString();
					this.Rows = reader.ReadInt32();
					this.Columns = reader.ReadInt32();
					this.TileSize = new Size(reader.ReadInt32(), reader.ReadInt32());

					this._tiles = new Nullable<Tile>[this.Rows, this.Columns];

					for (var row = 0; row < this.Rows; row++)
					{
						for (var col = 0; col < this.Columns; col++)
						{
							var used = reader.ReadBoolean();
							if (used == false)
								continue;

							var id = reader.ReadByte();
							var flag = reader.ReadByte();
							this._tiles[row, col] = new Tile(id, flag);
						}
					}

					var respawnPointCount = reader.ReadInt32();
					for (var i = 0; i < respawnPointCount; i++)
						this.RespawnPoints[reader.ReadInt32()] = new Point(reader.ReadInt32(), reader.ReadInt32());

					var enemyCount = reader.ReadInt32();
					for (var i = 0; i < enemyCount; i++)
						this.Enemies.Add(new Enemy(reader.ReadString(), new Point(reader.ReadInt32(), reader.ReadInt32())));
				}

				this.Sprite = sprite;
				return true;
			}
			catch (Exception e)
			{
				return false;
			}
		}

		public bool save(string filename, string bgmName)
		{
			try
			{
				using (var writer = new BinaryWriter(File.Open(filename, FileMode.Create)))
				{
					if (bgmName == null)
						writer.Write(string.Empty);
					else
						writer.Write(bgmName);

					writer.Write(this.Rows);
					writer.Write(this.Columns);
					writer.Write(this.TileSize.Width);
					writer.Write(this.TileSize.Height);
					for (var row = 0; row < this.Rows; row++)
					{
						for (var col = 0; col < this.Columns; col++)
						{
							var tile = this._tiles[row, col];
							var used = tile != null;
							writer.Write(used);

							if (used)
							{
								writer.Write(tile.Value.id);
								writer.Write(tile.Value.flag);
							}
						}
					}

					writer.Write(this.RespawnPointCount);
					for (var i = 0; i < this.RespawnPoints.Length; i++)
					{
						if (this.RespawnPoints[i] == null)
							continue;

						writer.Write(i);
						writer.Write(this.RespawnPoints[i].Value.X);
						writer.Write(this.RespawnPoints[i].Value.Y);
					}

					writer.Write(this.Enemies.Count);
					foreach (var enemy in this.Enemies)
					{
						writer.Write(enemy.name);
						writer.Write(enemy.point.X);
						writer.Write(enemy.point.Y);
					}
				}
				return true;
			}
			catch (Exception e)
			{
				return false;
			}
		}
	}
}
