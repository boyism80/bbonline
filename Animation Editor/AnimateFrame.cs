using System.Drawing;
using System.IO;

namespace AnimationEditor
{
    public class AnimateFrame
    {
        public float duration { get; set; }
        public Point position { get; set; }
        public string name { get; private set; }
        
        public AnimateFrame(string name, Point position, float duration)
        {
            this.name = name;
            this.position = position;
            this.duration = duration;
        }

        public void save(BinaryWriter writer)
        {
            writer.Write(name);
            writer.Write(duration);
            writer.Write(position.X);
            writer.Write(position.Y);
        }

        public static AnimateFrame load(BinaryReader reader)
        {
            var name = reader.ReadString();
            var duration = reader.ReadSingle();
            var x = reader.ReadInt32();
            var y = reader.ReadInt32();

            return new AnimateFrame(name, new Point(x, y), duration);
        }
    }
}