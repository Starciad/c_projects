# Uno

A terminal-based UNO game implementation in C with AI opponents and full rule support.

## Features

- Text-based game interface
- Complete official UNO rules
- AI system with varying strategies
- Multiplayer support (2-10 players)
- C standard libraries only
- Modular, easy-to-extend code

## Game Overview

UNO is a card game created by Merle Robbins in 1971. Players race to discard all their cards.

**Quick Facts:**

- Players: 2–10
- Cards: 108
- Playtime: 15–30 minutes

**Core Rules:**

- Start with 7 cards
- Play cards matching the top card by number, color, or type
- Draw a card if you can't play
- Declare "UNO" with one card left (penalty: draw 2)

**Special Cards:**

| Card               | Effect                                        |
| ------------------ | --------------------------------------------- |
| **Skip**           | Next player loses turn                        |
| **Reverse**        | Reverses turn order                           |
| **Draw Two**       | Next player draws 2, loses turn               |
| **Wild**           | Choose a color                                |
| **Wild Draw Four** | Choose color, next player draws 4, loses turn |
