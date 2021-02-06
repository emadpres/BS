using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace WindowsGame3
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        KeyboardState keyboard1;
        Texture2D t1;
        Rectangle rect1;
        Texture2D t2;
        Rectangle rect2;
        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            rect1 = new Rectangle(0, 0, 400, 400);
            rect2 = new Rectangle(500, 200, 100, 100);
            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            t1 = this.Content.Load<Texture2D>("Chrysanthemum");
            t2 = this.Content.Load<Texture2D>("Untitled-1");
            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();
            keyboard1 = Keyboard.GetState();
            if (keyboard1.IsKeyDown(Keys.Up))
            {
                if(rect2.Y-1!=0)
                    rect2.Y -= 1;
            }
            if(keyboard1.IsKeyDown(Keys.Down))
            {
                if(rect2.Y+1+rect2.Height!=GraphicsDevice.Viewport.Height)
                 rect2.Y+=1;
            }
            if(keyboard1.IsKeyDown(Keys.Left))
            {
                if (rect2.X - 1 != 0) 
                    rect2.X-=1;
            }
            if(keyboard1.IsKeyDown(Keys.Right))
            {
                if(rect2.X+1+rect2.Width!=GraphicsDevice.Viewport.Width)
                    rect2.X += 1;
            }
            if (keyboard1.IsKeyDown(Keys.Escape))
            {
                Exit();
            }
            // TODO: Add your update logic here

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.White);
            spriteBatch.Begin();
            spriteBatch.Draw(t1, rect1, Color.White);
            spriteBatch.Draw(t2, rect2, Color.White);
            spriteBatch.End();
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }
    }
}
