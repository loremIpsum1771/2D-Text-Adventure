***The files in this repository were created as a side-project and can be used as a base line template for making a text-based adventure game***

#Features

* **Storyline**
  * Built to follow a linear plot
  * Good for mystery games and the like
  
* **Map Initialization**
  * Renders Map by parsing specs of each room from a file
  * Code can be slightly adapted to work with different settings specified in the fiie
   
* **Navigation**
  * Navigation implemented with a 2-D array
  * Matrix can rotate + or - 90 degrees based on user's position in the map to maintain continuity of navigation
  
* **Player Inventory**
  * Player spawns with an inventory of weapons
  * Weapons and healthpacks can be picked up during the game
  * Each weapon is created with a different damage value
  
* **Combat Simulation** 
  * Dynamic simulation constructed to be re-used wherever a battle occurs in the map
  * Simple AI primarily based on random chance
  * User can either attack or dodge
  * Opponent can divert attacks or dodge and counter

###Sample use case for the file that is parsed to create the game
```
Inside your car |You are inside of your car parked outside of the scene where your person of interest was last seen and you are preparing to go inside.|0|0
closed room | Room Closed|0|2
closed room | Room Closed|0|3
closed room | Room Closed|1|3
closed room | Room Closed|3|0
closed room | Room Closed|3|1
closed room | Room Closed|3|2
closed room | Room Closed|3|3
Main Hallway |You can see that this hallway leads to several other rooms as well as a stairwell straight ahead. You decide to explore around.|1|1
Downstairs Dining Room |You can now see what looks like some kind of doctor's operation kit laying out on the table next to white cloths stained red. Could this be some kind of evidence?>|1|0
Living Room | You can now see furniture covered in some protective plasticed positioned all  around the room.|1|2
Upstairs hallway | You are now in the hall way on the second floor.|2|1
Bathroom | You can see lots of dark stains in the bathtub and a lot of hair in the sink and the trash.|2|0
foyer|You are now inside the house's foyer after deciding to enter. You can smell the age of the house and get an eerie feeling. You decide to investigate further.|0|1
Bedroom | You can see several beds with unconscious people laying down.|2|3
Operation Room | You can see a large operating table with an unconscious person sprawled out. There appears to be a division leading to another room|2|2
Missing Victim 3 $70$40$knife
Suspect $100$90$hatchet
healthPack = 20
hatchet!
```
  

