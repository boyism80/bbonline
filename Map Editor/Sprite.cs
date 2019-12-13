using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace SpriteEditor
{
	public class Sprite : IEnumerable<KeyValuePair<string, Sprite.Element>>
	{
		public enum Pivot
		{
			LeftTop = 0,
			LeftBottom = 1,
			RightTop = 2,
			RightBottom = 3,
			CenterTop = 4,
			CenterBottom = 5,
		}

		public class Element
		{
			public byte[] Bytes { get; set; }
			public Pivot Pivot { get; set; }

			public Element(byte[] bytes, Pivot pivot)
			{
				this.Bytes = bytes;
				this.Pivot = pivot;
			}
		}

		private Dictionary<string, Sprite.Element> _images = new Dictionary<string, Sprite.Element>();

		public Sprite()
		{ }

		public Sprite(string filename)
		{
			if (this.load(filename) == false)
				throw new FileNotFoundException();
		}

		public int Count
		{
			get
			{
				return this._images.Count;
			}
		}

		public bool load(string filename)
		{
			try
			{
				this._images.Clear();

				using (var reader = new BinaryReader(File.Open(filename, FileMode.Open)))
				{
					var count = reader.ReadInt32();
					for (var i = 0; i < count; i++)
					{
						var key = reader.ReadString();
						var pivot = (Pivot)reader.ReadInt32();
						var bytesLength = reader.ReadInt32();
						var bytes = reader.ReadBytes(bytesLength);

						this._images.Add(key, new Element(bytes, pivot));
					}
				}

				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

		public bool save(string filename)
		{
			try
			{
				using (var writer = new BinaryWriter(File.Open(filename, FileMode.Create)))
				{
					writer.Write(this._images.Count);

					foreach (var pair in this._images)
					{
						writer.Write(pair.Key);
						writer.Write((int)pair.Value.Pivot);
						writer.Write(pair.Value.Bytes.Length);
						writer.Write(pair.Value.Bytes);
					}
				}
				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

		public string add(string path, Pivot pivot)
		{
			try
			{
				var name = Path.GetFileName(path);
				this._images[name] = new Element(File.ReadAllBytes(path), pivot);
				return name;
			}
			catch (Exception)
			{
				return null;
			}
		}

		public void remove(string name)
		{
			try
			{
				this._images.Remove(name);
			}
			catch (Exception)
			{

			}
		}

		public bool rename(string src, string dest)
		{
			try
			{
				if (src.Equals(dest))
					return true;

				this._images[dest] = this._images[src];
				this._images.Remove(src);
				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

		public void clear()
		{
			this._images.Clear();
		}

		IEnumerator<KeyValuePair<string, Sprite.Element>> IEnumerable<KeyValuePair<string, Sprite.Element>>.GetEnumerator()
		{
			return this._images.GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			return this._images.GetEnumerator();
		}

		public Element this[string name]
		{
			get
			{
				return this._images[name];
			}
		}
	}
}
