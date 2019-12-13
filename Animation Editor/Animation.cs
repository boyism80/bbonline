using SpriteEditor;
using System;
using System.Collections.Generic;
using System.IO;

namespace AnimationEditor
{
    public class Animation
    {
        public AnimateAction currentAction { get; private set; }

        public Dictionary<string, AnimateAction> animateActions { get; private set; }
        public Sprite Sprite { get; private set; }
        

        public Animation(string spriteFileName)
        {
			this.Sprite = new Sprite(spriteFileName);
            this.animateActions = new Dictionary<string, AnimateAction>();
        }

		public Animation(Sprite sprite)
		{
			this.animateActions = new Dictionary<string, AnimateAction>();
			this.Sprite = sprite;
		}

		public Animation(string filename, string spriteFileName)
		{
			this.animateActions = new Dictionary<string, AnimateAction>();
			this.load(filename, new Sprite(spriteFileName));
		}

		public Animation(string filename, Sprite sprite)
		{
			this.animateActions = new Dictionary<string, AnimateAction>();
			this.load(filename, sprite);
		}

		public bool save(string filename)
		{
			try
			{
				using (var writer = new BinaryWriter(File.Open(filename, FileMode.Create)))
				{
					writer.Write(this.animateActions.Count);
					foreach (var pair in this.animateActions)
						pair.Value.save(writer);
				}

				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

        public void load(BinaryReader reader)
        {
            var count = reader.ReadInt32();
            for(var i = 0; i < count; i++)
            {
                var animateAction = AnimateAction.load(reader);
                this.animateActions.Add(animateAction.name, animateAction);
            }
        }

		public bool load(string filename, Sprite sprite)
		{
			this.Sprite = sprite;
			try
			{
				using (var reader = new BinaryReader(File.Open(filename, FileMode.Open)))
				{
					var count = reader.ReadInt32();
					for (var i = 0; i < count; i++)
					{
						var animateAction = AnimateAction.load(reader);
						this.animateActions.Add(animateAction.name, animateAction);
					}
				}
				return true;
			}
			catch (Exception)
			{
				return false;
			}
		}

        public bool change(string name)
        {
            if(this.animateActions.ContainsKey(name) == false)
                return false;

            if(this.currentAction != null)
                this.currentAction.reset();
            this.currentAction = this.animateActions[name];
            return true;
        }

        public void reset()
        {
            if(this.currentAction != null)
                this.currentAction.reset();
        }
    }
}