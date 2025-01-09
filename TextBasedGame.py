# Jacob Perry

intro_art = '''
            .▄▄ · ▄▄▌   ▄▄▄·  ▄· ▄▌▪   ▐ ▄  ▄▄ •     ▄▄▄▄▄ ▄ .▄▄▄▄ .              
            ▐█ ▀. ██•  ▐█ ▀█ ▐█▪██▌██ •█▌▐█▐█ ▀ ▪    •██  ██▪▐█▀▄.▀·              
            ▄▀▀▀█▄██▪  ▄█▀▀█ ▐█▌▐█▪▐█·▐█▐▐▌▄█ ▀█▄     ▐█.▪██▀▐█▐▀▀▪▄              
            ▐█▄▪▐█▐█▌▐▌▐█ ▪▐▌ ▐█▀·.▐█▌██▐█▌▐█▄▪▐█     ▐█▌·██▌▐▀▐█▄▄▌              
             ▀▀▀▀ .▀▀▀  ▀  ▀   ▀ • ▀▀▀▀▀ █▪·▀▀▀▀      ▀▀▀ ▀▀▀ · ▀▀▀               
▄▄▄ .▄▄▌  ▄▄▄ .• ▌ ▄ ·. ▄▄▄ . ▐ ▄ ▄▄▄▄▄ ▄▄▄· ▄▄▌      ▄▄▄▄· ▄▄▄ . ▄▄▄· .▄▄ · ▄▄▄▄▄
▀▄.▀·██•  ▀▄.▀··██ ▐███▪▀▄.▀·•█▌▐█•██  ▐█ ▀█ ██•      ▐█ ▀█▪▀▄.▀·▐█ ▀█ ▐█ ▀. •██  
▐▀▀▪▄██▪  ▐▀▀▪▄▐█ ▌▐▌▐█·▐▀▀▪▄▐█▐▐▌ ▐█.▪▄█▀▀█ ██▪      ▐█▀▀█▄▐▀▀▪▄▄█▀▀█ ▄▀▀▀█▄ ▐█.▪
▐█▄▄▌▐█▌▐▌▐█▄▄▌██ ██▌▐█▌▐█▄▄▌██▐█▌ ▐█▌·▐█ ▪▐▌▐█▌▐▌    ██▄▪▐█▐█▄▄▌▐█ ▪▐▌▐█▄▪▐█ ▐█▌·
 ▀▀▀ .▀▀▀  ▀▀▀ ▀▀  █▪▀▀▀ ▀▀▀ ▀▀ █▪ ▀▀▀  ▀  ▀ .▀▀▀     ·▀▀▀▀  ▀▀▀  ▀  ▀  ▀▀▀▀  ▀▀▀ 
'''


def status(current_room, inventory, rooms):
    print('You are in the {}'.format(current_room))  # displays room player is currently in
    print('Inventory: {}'.format(inventory))  # displays current contents of player's inventory
    if 'item' in rooms[current_room]:  # checks to see if a collectable item is in current room
        print('You see an item: {}'.format(rooms[current_room]['item']))  # tells player available item in room


def intro():
    print(intro_art)
    print('Welcome to my text-based game; Slaying the Elemental Beast!')
    print('You must collect all 6 items before you encounter the Elemental Beast.')
    print('If you fail to collect all of the items before you run into the beast, you will be meet an unpleasant end.')
    print("Your commands to move are as follows:\n'go South', 'go North', 'go East', 'go West' and 'exit'.")
    print('To add an item to your inventory:\n \'get "item name"\'.')


def new_move():
    user_move = input("Enter your move: ").title().split()  # converts user input to typecase, and into a list
    return user_move

def main():
    rooms = {
        'Abandoned Town Center': {'South': 'Tattered Old Altar', 'North': 'Small Pond', 'East': 'Mining Pit',
                                  'West': 'Tavern'},
        'Tattered Old Altar': {'North': 'Abandoned Town Center', 'East': 'Outskirts of Town', 'item': 'Fire Arrows'},
        'Outskirts of Town': {'West': 'Tattered Old Altar', 'villain': 'Beast'},
        'Tavern': {'East': 'Abandoned Town Center', 'item': 'Bow'},
        'Small Pond': {'South': 'Abandoned Town Center', 'East': 'Old Barn', 'item': 'Ice Arrows'},
        'Old Barn': {'West': 'Small Pond', 'item': 'Electric Arrows'},
        'Mining Pit': {'West': 'Abandoned Town Center', 'North': 'Tool Shed', 'item': 'Stone Arrows'},
        'Tool Shed': {'South': 'Mining Pit', 'item': 'Quiver'}
    }

    current_room = 'Abandoned Town Center'
    directions = ['North', 'South', 'East', 'West']
    inventory = []

    print("*****************************************")

    status(current_room, inventory, rooms)

    user_move = new_move()

    while user_move != ['Exit']:  # allows user to exit game if they input 'exit'
        print("*****************************************")
        if user_move[0] == 'Go' and user_move[1] in directions:  # checks user input to verify a valid command was given
            if user_move[1] in rooms[current_room]:  # checks to see if user can move with the given direction
                current_room = rooms[current_room][user_move[1]]  # puts user in new room
                status(current_room, inventory, rooms)
            else:
                print('You can\'t go that way, try again!')

            if current_room == 'Outskirts of Town':  # checks to see if player wins or loses when getting to beast
                if len(inventory) < 6:
                    print('You encountered the beast before acquiring all 6 items. You have been killed.')
                    break  # ends while loop so game ends after encounter
                elif len(inventory) == 6:
                    print('You found all 6 items and encountered the elemental beast.\n'
                          'You use each of your items accordingly and successfully slay the beast. You have won!')
                    break  # ends while loop so game ends after encounter
        elif user_move[0] == 'Get':  # checks if player is trying to collect an item
            del user_move[0]  # makes user_move into just name of item
            user_move = ' '.join(user_move)  # converts back into string to compare to 'item' in dictionary
            if user_move == rooms[current_room]['item']:
                inventory.append(rooms[current_room]['item'])  # adds item to inventory if possible
                del rooms[current_room]['item']  # removes item from current room, so it cannot be gathered twice
                status(current_room, inventory, rooms)
            else:
                print('Invalid move, try again!')
                status(current_room, inventory, rooms)

        else:
            print('Invalid move, try again!')
            status(current_room, inventory, rooms)

        user_move = input("Enter your move: ").title().split()


intro()
main()
print('\nThanks for playing! :)')