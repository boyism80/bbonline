using SpriteEditor;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;

public class Window
{
    public string Id { get; set; }
    public string SpriteName { get; set; }
	public Point Location { get; set; }
    public Size Size { get; set; }
    public string Purpose { get; set; }
    public string Text { get; set; }
    public Sprite Sprite { get; protected set; }
    public Window Parent { get; set; }
    public bool isVisible { get; set; }

	public List<Window> Controls { get; private set; }

    
    public Window(string id, string spriteName, Window parent, int x, int y, int winWidth, int winHeight, string purpose, string text, bool visible, Sprite sprite)
    {
        this.Id = id;
        this.SpriteName = spriteName;
		this.Parent = parent;
		this.Location = new Point(x, y);
        this.Size = new Size(winWidth, winHeight);
        this.Purpose = purpose;
        this.Text = text;
        this.Sprite = sprite;
		this.Controls = new List<Window>();
        this.isVisible = visible;
    }

    public Window(Sprite sprite, BinaryReader reader, Window parent)
    {
		this.Controls = new List<Window>();
        this.Parent = parent;
        if (this.load(sprite, reader) == false)
            throw new FileNotFoundException();
    }

    public virtual bool load(Sprite sprite, BinaryReader reader)
    {
        try
        {
			this.Sprite = sprite;
			this.Id = reader.ReadString();
            this.SpriteName = reader.ReadString();
            this.Location = new Point(reader.ReadInt32(), reader.ReadInt32());
            this.Size = new Size(reader.ReadInt32(), reader.ReadInt32());
            this.Purpose = reader.ReadString();
            this.Text = reader.ReadString();
            this.isVisible = reader.ReadBoolean();

            var controlsCount = reader.ReadInt32();
			for (var i = 0; i < controlsCount; i++)
				this.Controls.Add(new Window(sprite, reader, this));
        }
        catch (Exception exc)
        {
            return false;
        }

        return true;
    }

    public virtual bool Save(BinaryWriter writer)
    {
        try
        {
			writer.Write(this.Id);
			writer.Write(this.SpriteName);
			writer.Write(this.Location.X);
			writer.Write(this.Location.Y);
			writer.Write(this.Size.Width);
			writer.Write(this.Size.Height);
			writer.Write(this.Purpose);
			writer.Write(this.Text);
            writer.Write(this.isVisible);

            writer.Write(this.Controls.Count);
			foreach (var control in this.Controls)
				control.Save(writer);
        }
        catch (Exception)
        {
            return false;
        }

        return true;
    }
}
