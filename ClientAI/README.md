# Zappy Client AI

# Table of Contents

[Introduction](#.Introduction)
[Installation](#.Installation)
[Usage](#.Usage)
[Features](#.Features)
[Configuration](#.Configuration)
[Api](#.API)
[License](#.License)


# Introduction
The Zappy Client AI is an integral component of the Zappy project, designed to provide intelligent and autonomous behavior for the client-side interaction with the game server. It leverages artificial intelligence algorithms to make informed decisions and execute actions in the game environment.

The main objective of the Zappy Client AI is to efficiently control a team of virtual players (also known as "eggs") to collect resources, build structures, and defend against hostile entities. It acts as an intelligent agent that communicates with the game server, gathers information about the game state, and makes strategic decisions to maximize the team's chances of success.

Powered by advanced AI algorithms, the Zappy Client AI incorporates various techniques such as pathfinding, resource management, collaborative decision-making, and adaptive strategies. These techniques enable the AI to adapt to dynamic game conditions, optimize resource allocation, and coordinate actions with other team members.

There'll be some random event on the planet like birth, meteorites crashing on the planet and the AI will have to adapt to it.

# Installation
For the installation part, for the moment i use pygame to create the clock in the game and to install pygame you can use the following command:
sudo dnf install python3-pygame

# Usage
To "run" the game you need first to do make or make re and then you can launch the client ai with the following command:
./zappy_ai -p [Port where the server is lunch] -n team_name -h [Ip where the server is lunch (localhost if you are on the same machine as the server)]

# Features
The Zappy Client AI offers a range of powerful features that contribute to its effectiveness and strategic gameplay. Some of the key features include:

#   Intelligent Decision-Making
    The Zappy Client AI employs advanced algorithms to make intelligent decisions based on the current game state. It analyzes available information, such as resource locations, opponent positions, and team dynamics, to determine the most optimal actions to take. This allows the AI to adapt to changing circumstances and make informed choices.

#   Pathfinding and Navigation
    To efficiently navigate the game world, the Zappy Client AI utilizes robust pathfinding algorithms. It calculates the shortest and most efficient paths to reach desired locations, avoiding obstacles and optimizing movement. This ensures that the AI can move quickly and effectively across the game environment.

#   Resource Management
    Efficient resource management is a key aspect of successful gameplay in Zappy. The Zappy Client AI incorporates resource management strategies to ensure the team's resources are utilized effectively. It tracks resource levels, plans resource gathering routes, and distributes tasks among team members to optimize resource collection and utilization.

#   Collaborative Decision-Making
    The Zappy Client AI fosters collaboration among team members by facilitating communication and coordination. It shares information and strategies with other team members, enabling cooperative decision-making and synchronized actions. This collaborative approach enhances team efficiency and effectiveness in achieving shared goals.

#   Adaptive Strategies
    The Zappy Client AI dynamically adapts its strategies based on the game environment and opponent behavior. It continuously assesses the situation, identifies threats, and adjusts its approach to counter opponent actions. This adaptive behavior allows the AI to react promptly and intelligently to changing circumstances.

# Configuration
With Vincent, we don't currently have any idea of how we can configure the AI, but we think we'll do next to the nb of population,
there'll be some percentage of AI just tell where are they, some percentage of AI just tell where the ressources are and some percentage of AI just go and take the ressources.

# API
For the moment we use pygame: https://www.pygame.org/news, to create our clock.

# License
Need to Specify the license.