import discord
from discord.ext import commands
import os
import subprocess

#invite link: https://discord.com/oauth2/authorize?client_id=931006649815167006&permissions=274877908992&scope=bot

token = "OTMxMDA2NjQ5ODE1MTY3MDA2.Yd-Jgg.OWTvr36IVLaVGukaJ8AEg3q9mug"
bot = commands.Bot(command_prefix='!')

# Bot needs to cd into cmake-build-debug, the run ./Boa

@bot.event
async def on_ready():
    print("Logged in as")
    print(bot.user.name)
    print(bot.user.id)
    print("------")

# Strings have to use ' ' instead of " "
@bot.event
async def on_message(message):
    content = message.content
    if content.startswith('!run'):
        text = content[4:content.rfind('`')-2]
        backTickCount = 0

        fTxt = ""
        args = content[content.rfind('`')+1:len(content)]
        args = args.split(' ')

        for i in range(len(text)):
            if text[i] == '`':
                backTickCount += 1
                if backTickCount <= 3: continue
            fTxt += text[i]

        path = "/Users/preetithorat/Documents/GitHub/Boa/Discordbot/to_run.boa"

        with open(path, 'w') as tmp:
            tmp.truncate(0)
            tmp.write("running = true")
            tmp.write(fTxt)
            tmp.close()
            print("File written")
            sub = subprocess.Popen(["boa", path], stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
            for arg in args:
                print(arg)

            lines = sub.stdout.readlines()
            output = []
            for line in lines:
                output.append(line.decode('utf-8'))
            print(output)
            print(output)
            execTime = output[len(output)-1]

            if output[0].startswith("Traceback"):
                error = output[len(output)-4]
                errorUnderline = output[len(output)-3]
                errorUnderline = errorUnderline.replace(" ", "-")
                output[len(output)-3] = errorUnderline

            strOut = ""

            for i in range(len(output) - 1):
                strOut += output[i]

            print(strOut)

            if strOut.startswith("Traceback"):
                embed = discord.Embed(
                    title="Error here:",
                    description = error + "\n" + errorUnderline,
                    color=discord.Color.red()
                )
                embed.add_field(
                    name="Output",
                    value="```" + strOut + "```",
                    inline=False
                )
            else:
                embed = discord.Embed(
                    title="Finished Executing",
                    description=execTime,
                    color=discord.Color.green()
                )
                embed.add_field(
                    name="Output",
                    value="```" + strOut + "```",
                    inline=False
                )
            await message.channel.send(embed=embed, reference=message)

bot.run(token)

