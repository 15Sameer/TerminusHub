// // hangman.cpp (fully upgraded with complete difficulty-based hints)

// #include "hangman.hpp"
// #include <ncurses.h>
// #include <cstdlib>
// #include <ctime>
// #include <algorithm>
// #include <cctype>
// #include <unordered_map>

// Hangman::Hangman() : difficulty(1), gameOver(false), wrongGuesses(0) {
//     srand(static_cast<unsigned>(time(0)));
//     loadWords();
//     score = 0;
//     currentCategory = "Animals";
// }

// Hangman::~Hangman() {}

// void Hangman::setDifficulty(int d) {
//     difficulty = d;
// }

// void Hangman::loadWords() {
//     categories.clear();
//     // Categories
//     categories["Animals"] = {"cat", "lion", "penguin", "elephant", "zebra", "giraffe", "kangaroo", "tiger", "bear", "wolf", "fox", "monkey", "rabbit", "panda", "whale", "shark", "eagle", "owl", "dolphin", "leopard", "hippo", "rhino", "deer", "cheetah", "squirrel"};
//     categories["Food"] = {"pizza", "pasta", "samosa", "biryani", "waffle", "burger", "noodles", "salad", "cheese", "steak", "omelette", "pancake", "bacon", "sausage", "donut", "cookie", "curry", "sandwich", "soup", "lasagna", "dumpling", "kebab", "toast", "fries", "risotto"};
//     categories["Movies"] = {"titanic", "inception", "joker", "frozen", "avatar", "gladiator", "shrek", "matrix", "coco", "up", "batman", "superman", "psycho", "notebook", "memento", "aladdin", "gravity", "jaws", "rocky", "casablanca", "interstellar", "tenet", "dune", "zootopia", "moana"};
//     categories["Sports"] = {"cricket", "tennis", "boxing", "karate", "skiing", "soccer", "golf", "rugby", "hockey", "cycling", "swimming", "badminton", "volleyball", "surfing", "archery", "fencing", "rowing", "skating", "baseball", "basketball", "climbing", "wrestling", "diving", "sailing", "gymnastics"};
//     categories["Countries"] = {"india", "japan", "brazil", "kenya", "france", "canada", "germany", "china", "italy", "spain", "russia", "mexico", "australia", "turkey", "norway", "sweden", "greece", "argentina", "chile", "egypt", "nigeria", "thailand", "indonesia", "vietnam", "portugal"};
//     sessionCategories = categories;

//     wordHintsEasy.clear();
//     wordHintsMedium.clear();
//     wordHintsHard.clear();

//     // === EASY HINTS (Direct descriptions) ===
//     // Animals
//     wordHintsEasy["cat"] = "A small domesticated feline animal.";
//     wordHintsEasy["lion"] = "King of the jungle with a mane.";
//     wordHintsEasy["penguin"] = "A flightless bird often seen in Antarctica.";
//     wordHintsEasy["elephant"] = "The largest land animal.";
//     wordHintsEasy["zebra"] = "Horse-like animal with black-and-white stripes.";
//     wordHintsEasy["giraffe"] = "The tallest living terrestrial animal.";
//     wordHintsEasy["kangaroo"] = "Australian marsupial that hops.";
//     wordHintsEasy["tiger"] = "Striped big cat, predator.";
//     wordHintsEasy["bear"] = "Large mammal known for hibernation.";
//     wordHintsEasy["wolf"] = "Wild ancestor of the domestic dog.";
//     wordHintsEasy["fox"] = "A clever red-furred animal.";
//     wordHintsEasy["monkey"] = "Primates that love swinging from trees.";
//     wordHintsEasy["rabbit"] = "Furry animal with long ears.";
//     wordHintsEasy["panda"] = "Black-and-white bear that eats bamboo.";
//     wordHintsEasy["whale"] = "Huge ocean-dwelling mammal.";
//     wordHintsEasy["shark"] = "Predator fish with sharp teeth.";
//     wordHintsEasy["eagle"] = "A majestic bird of prey.";
//     wordHintsEasy["owl"] = "Nocturnal bird that hoots.";
//     wordHintsEasy["dolphin"] = "Intelligent marine mammal.";
//     wordHintsEasy["leopard"] = "Spotted wild feline predator.";
//     wordHintsEasy["hippo"] = "Huge semi-aquatic African mammal.";
//     wordHintsEasy["rhino"] = "Large mammal with horns.";
//     wordHintsEasy["deer"] = "Forest animal with antlers.";
//     wordHintsEasy["cheetah"] = "Fastest land animal.";
//     wordHintsEasy["squirrel"] = "Tree climber that gathers nuts.";

//     // Food
//     wordHintsEasy["pizza"] = "Italian dish with toppings on dough.";
//     wordHintsEasy["pasta"] = "Italian noodles in many shapes.";
//     wordHintsEasy["samosa"] = "Fried triangular Indian snack.";
//     wordHintsEasy["biryani"] = "Fragrant rice dish with spices.";
//     wordHintsEasy["waffle"] = "Grid-patterned breakfast cake.";
//     wordHintsEasy["burger"] = "A sandwich with a meat patty.";
//     wordHintsEasy["noodles"] = "Long strands of pasta or ramen.";
//     wordHintsEasy["salad"] = "Mix of veggies, sometimes with dressing.";
//     wordHintsEasy["cheese"] = "Dairy product, often yellow or white.";
//     wordHintsEasy["steak"] = "Grilled or pan-fried meat slice.";
//     wordHintsEasy["omelette"] = "Cooked eggs folded with fillings.";
//     wordHintsEasy["pancake"] = "Flat breakfast cake.";
//     wordHintsEasy["bacon"] = "Crispy meat strips from pigs.";
//     wordHintsEasy["sausage"] = "Ground meat in a casing.";
//     wordHintsEasy["donut"] = "Sweet fried ring-shaped treat.";
//     wordHintsEasy["cookie"] = "Small sweet baked dessert.";
//     wordHintsEasy["curry"] = "Spicy stew often from India.";
//     wordHintsEasy["sandwich"] = "Bread with fillings in between.";
//     wordHintsEasy["soup"] = "Warm liquid dish.";
//     wordHintsEasy["lasagna"] = "Layered pasta dish with cheese.";
//     wordHintsEasy["dumpling"] = "Stuffed dough cooked by boiling or frying.";
//     wordHintsEasy["kebab"] = "Grilled meat on a skewer.";
//     wordHintsEasy["toast"] = "Bread browned by heat.";
//     wordHintsEasy["fries"] = "Thin sticks of fried potato.";
//     wordHintsEasy["risotto"] = "Creamy Italian rice dish.";

//     // Movies
//     wordHintsEasy["titanic"] = "Ship disaster romance with DiCaprio.";
//     wordHintsEasy["inception"] = "Dreams within dreams thriller.";
//     wordHintsEasy["joker"] = "Batman's arch-nemesis origin story.";
//     wordHintsEasy["frozen"] = "Disney movie about ice powers.";
//     wordHintsEasy["avatar"] = "Blue aliens on Pandora.";
//     wordHintsEasy["gladiator"] = "Roman warrior who fought for sport.";
//     wordHintsEasy["shrek"] = "Green ogre who lives in a swamp.";
//     wordHintsEasy["matrix"] = "Neo discovers a virtual reality.";
//     wordHintsEasy["coco"] = "A Pixar film about music and memory.";
//     wordHintsEasy["up"] = "An old man flies with balloons.";
//     wordHintsEasy["batman"] = "Masked vigilante of Gotham.";
//     wordHintsEasy["superman"] = "Alien hero from Krypton.";
//     wordHintsEasy["psycho"] = "Horror movie by Alfred Hitchcock.";
//     wordHintsEasy["notebook"] = "Romantic movie based on a novel.";
//     wordHintsEasy["memento"] = "Story told backward about memory loss.";
//     wordHintsEasy["aladdin"] = "Street boy with a magic lamp.";
//     wordHintsEasy["gravity"] = "Two astronauts stuck in space.";
//     wordHintsEasy["jaws"] = "Movie about a killer shark.";
//     wordHintsEasy["rocky"] = "Boxer's underdog story.";
//     wordHintsEasy["casablanca"] = "Classic romantic film during war.";
//     wordHintsEasy["interstellar"] = "Time-bending space exploration film.";
//     wordHintsEasy["tenet"] = "Action thriller with time inversion.";
//     wordHintsEasy["dune"] = "Sci-fi movie set on Arrakis.";
//     wordHintsEasy["zootopia"] = "Animated city of talking animals.";
//     wordHintsEasy["moana"] = "Island girl sails to save the world.";

//     // Sports
//     wordHintsEasy["cricket"] = "Bat and ball sport popular in England.";
//     wordHintsEasy["tennis"] = "Racket sport with a net.";
//     wordHintsEasy["boxing"] = "Fighting sport using gloves.";
//     wordHintsEasy["karate"] = "Japanese martial art.";
//     wordHintsEasy["skiing"] = "Snow sport using skis.";
//     wordHintsEasy["soccer"] = "Football played around the world.";
//     wordHintsEasy["golf"] = "Sport with clubs and holes.";
//     wordHintsEasy["rugby"] = "Contact sport similar to football.";
//     wordHintsEasy["hockey"] = "Ice or field team sport.";
//     wordHintsEasy["cycling"] = "Sport using a bicycle.";
//     wordHintsEasy["swimming"] = "Moving in water for sport.";
//     wordHintsEasy["badminton"] = "Racquet game with a shuttlecock.";
//     wordHintsEasy["volleyball"] = "Game with a ball over a net.";
//     wordHintsEasy["surfing"] = "Riding ocean waves on a board.";
//     wordHintsEasy["archery"] = "Shooting arrows with a bow.";
//     wordHintsEasy["fencing"] = "Sword-fighting sport.";
//     wordHintsEasy["rowing"] = "Team boat racing with oars.";
//     wordHintsEasy["skating"] = "Gliding on wheels or blades.";
//     wordHintsEasy["baseball"] = "American bat-and-ball sport.";
//     wordHintsEasy["basketball"] = "Game of hoops and dribbles.";
//     wordHintsEasy["climbing"] = "Ascending rocks or walls.";
//     wordHintsEasy["wrestling"] = "Grappling combat sport.";
//     wordHintsEasy["diving"] = "Jumping into water gracefully.";
//     wordHintsEasy["sailing"] = "Using wind to power boats.";
//     wordHintsEasy["gymnastics"] = "Acrobatic sport with routines.";

//     // Countries
//     wordHintsEasy["india"] = "Bollywood and curry homeland.";
//     wordHintsEasy["japan"] = "Land of the rising sun.";
//     wordHintsEasy["brazil"] = "Famous for football and carnival.";
//     wordHintsEasy["kenya"] = "Known for wildlife and runners.";
//     wordHintsEasy["france"] = "Eiffel Tower and croissants.";
//     wordHintsEasy["canada"] = "Land of maple syrup.";
//     wordHintsEasy["germany"] = "Famous for engineering and Oktoberfest.";
//     wordHintsEasy["china"] = "Great Wall and fast tech.";
//     wordHintsEasy["italy"] = "Pizza, pasta, and Rome.";
//     wordHintsEasy["spain"] = "Flamenco and fiestas.";
//     wordHintsEasy["russia"] = "Largest country in the world.";
//     wordHintsEasy["mexico"] = "Home of tacos and Aztecs.";
//     wordHintsEasy["australia"] = "Kangaroos and the outback.";
//     wordHintsEasy["turkey"] = "Bridges Europe and Asia.";
//     wordHintsEasy["norway"] = "Land of fjords.";
//     wordHintsEasy["sweden"] = "Home of ABBA and IKEA.";
//     wordHintsEasy["greece"] = "Cradle of western civilization.";
//     wordHintsEasy["argentina"] = "Famous for tango and Messi.";
//     wordHintsEasy["chile"] = "Long coastal nation of South America.";
//     wordHintsEasy["egypt"] = "Pyramids and ancient history.";
//     wordHintsEasy["nigeria"] = "Most populous African nation.";
//     wordHintsEasy["thailand"] = "Known for beaches and cuisine.";
//     wordHintsEasy["indonesia"] = "Archipelago nation with many islands.";
//     wordHintsEasy["vietnam"] = "Pho and historical wars.";
//     wordHintsEasy["portugal"] = "Lisbon and custard tarts.";

//     // === MEDIUM HINTS (Clues and characteristics) ===
//     // Animals
//     wordHintsMedium["cat"] = "Purrs when content, has retractable claws.";
//     wordHintsMedium["lion"] = "Lives in prides, roars loudly.";
//     wordHintsMedium["penguin"] = "Waddles on ice, excellent swimmer.";
//     wordHintsMedium["elephant"] = "Never forgets, has a trunk.";
//     wordHintsMedium["zebra"] = "No two have identical patterns.";
//     wordHintsMedium["giraffe"] = "Purple tongue, ossicones on head.";
//     wordHintsMedium["kangaroo"] = "Carries babies in a pouch.";
//     wordHintsMedium["tiger"] = "Solitary hunter, orange and black.";
//     wordHintsMedium["bear"] = "Sleeps through winter months.";
//     wordHintsMedium["wolf"] = "Travels in packs, howls at moon.";
//     wordHintsMedium["fox"] = "Bushy tail, cunning reputation.";
//     wordHintsMedium["monkey"] = "Opposable thumbs, social creatures.";
//     wordHintsMedium["rabbit"] = "Thumps hind legs when scared.";
//     wordHintsMedium["panda"] = "Endangered Chinese bear species.";
//     wordHintsMedium["whale"] = "Communicates through songs.";
//     wordHintsMedium["shark"] = "Cartilaginous skeleton, multiple rows of teeth.";
//     wordHintsMedium["eagle"] = "National bird of several countries.";
//     wordHintsMedium["owl"] = "Can turn head 270 degrees.";
//     wordHintsMedium["dolphin"] = "Echolocation for navigation.";
//     wordHintsMedium["leopard"] = "Excellent climber, nocturnal hunter.";
//     wordHintsMedium["hippo"] = "Spends most day in water.";
//     wordHintsMedium["rhino"] = "Poor eyesight, excellent hearing.";
//     wordHintsMedium["deer"] = "Males shed antlers annually.";
//     wordHintsMedium["cheetah"] = "Can't roar, only chirps and purrs.";
//     wordHintsMedium["squirrel"] = "Buries nuts for winter storage.";

//     // Food
//     wordHintsMedium["pizza"] = "Originated in Naples, Italy.";
//     wordHintsMedium["pasta"] = "Made from durum wheat semolina.";
//     wordHintsMedium["samosa"] = "Often filled with potatoes and peas.";
//     wordHintsMedium["biryani"] = "Layered rice dish with saffron.";
//     wordHintsMedium["waffle"] = "Cooked in a special iron press.";
//     wordHintsMedium["burger"] = "Often served with lettuce and tomato.";
//     wordHintsMedium["noodles"] = "Can be made from rice or wheat.";
//     wordHintsMedium["salad"] = "Often dressed with oil and vinegar.";
//     wordHintsMedium["cheese"] = "Aged varieties have stronger flavors.";
//     wordHintsMedium["steak"] = "Cooking levels from rare to well-done.";
//     wordHintsMedium["omelette"] = "French technique, beaten eggs folded.";
//     wordHintsMedium["pancake"] = "Leavened with baking powder or soda.";
//     wordHintsMedium["bacon"] = "Cured and smoked pork belly.";
//     wordHintsMedium["sausage"] = "Often seasoned with herbs and spices.";
//     wordHintsMedium["donut"] = "Deep-fried in oil, often glazed.";
//     wordHintsMedium["cookie"] = "Can be soft-baked or crispy.";
//     wordHintsMedium["curry"] = "Uses blend of ground spices.";
//     wordHintsMedium["sandwich"] = "Named after Earl of Sandwich.";
//     wordHintsMedium["soup"] = "Can be served hot or cold.";
//     wordHintsMedium["lasagna"] = "Baked pasta dish with bechamel.";
//     wordHintsMedium["dumpling"] = "Wrapper can be steamed or fried.";
//     wordHintsMedium["kebab"] = "Meat marinated before grilling.";
//     wordHintsMedium["toast"] = "Maillard reaction creates browning.";
//     wordHintsMedium["fries"] = "Twice-cooked for extra crispiness.";
//     wordHintsMedium["risotto"] = "Stirred constantly while cooking.";

//     // Movies
//     wordHintsMedium["titanic"] = "1997 disaster romance, 11 Oscars.";
//     wordHintsMedium["inception"] = "Christopher Nolan's dream heist.";
//     wordHintsMedium["joker"] = "Joaquin Phoenix won Oscar for role.";
//     wordHintsMedium["frozen"] = "Let it go, let it go...";
//     wordHintsMedium["avatar"] = "Highest-grossing film for a decade.";
//     wordHintsMedium["gladiator"] = "Are you not entertained?";
//     wordHintsMedium["shrek"] = "Mike Myers voices green protagonist.";
//     wordHintsMedium["matrix"] = "Choose the red or blue pill.";
//     wordHintsMedium["coco"] = "Remember me, though I have to travel far.";
//     wordHintsMedium["up"] = "Adventure is out there!";
//     wordHintsMedium["batman"] = "I'm not wearing hockey pads.";
//     wordHintsMedium["superman"] = "Faster than a speeding bullet.";
//     wordHintsMedium["psycho"] = "Shower scene is iconic.";
//     wordHintsMedium["notebook"] = "If you're a bird, I'm a bird.";
//     wordHintsMedium["memento"] = "Guy Pearce has memory issues.";
//     wordHintsMedium["aladdin"] = "A whole new world awaits.";
//     wordHintsMedium["gravity"] = "Sandra Bullock in space debris.";
//     wordHintsMedium["jaws"] = "You're gonna need a bigger boat.";
//     wordHintsMedium["rocky"] = "Going the distance with Apollo.";
//     wordHintsMedium["casablanca"] = "Here's looking at you, kid.";
//     wordHintsMedium["interstellar"] = "Love transcends dimensions.";
//     wordHintsMedium["tenet"] = "Don't try to understand it, feel it.";
//     wordHintsMedium["dune"] = "The spice must flow on desert planet.";
//     wordHintsMedium["zootopia"] = "Anyone can be anything in this city.";
//     wordHintsMedium["moana"] = "The ocean chose her for a quest.";

//     // Sports
//     wordHintsMedium["cricket"] = "Played with wickets and overs.";
//     wordHintsMedium["tennis"] = "Love means zero in scoring.";
//     wordHintsMedium["boxing"] = "Sweet science of hit and don't get hit.";
//     wordHintsMedium["karate"] = "Empty hand fighting technique.";
//     wordHintsMedium["skiing"] = "Downhill or cross-country variants.";
//     wordHintsMedium["soccer"] = "90 minutes plus injury time.";
//     wordHintsMedium["golf"] = "Par is the standard score.";
//     wordHintsMedium["rugby"] = "15 players per side in union.";
//     wordHintsMedium["hockey"] = "Puck or ball depending on surface.";
//     wordHintsMedium["cycling"] = "Peloton rides together in races.";
//     wordHintsMedium["swimming"] = "Four main strokes in competition.";
//     wordHintsMedium["badminton"] = "Shuttlecock made from feathers.";
//     wordHintsMedium["volleyball"] = "Six players per side, net height matters.";
//     wordHintsMedium["surfing"] = "Pipeline and barrel are famous moves.";
//     wordHintsMedium["archery"] = "Robin Hood was legendary at this.";
//     wordHintsMedium["fencing"] = "Foil, epee, and sabre are weapons.";
//     wordHintsMedium["rowing"] = "Crew sport with coxswain calling rhythm.";
//     wordHintsMedium["skating"] = "Figure or speed variants exist.";
//     wordHintsMedium["baseball"] = "Nine innings, three strikes you're out.";
//     wordHintsMedium["basketball"] = "Invented by James Naismith in 1891.";
//     wordHintsMedium["climbing"] = "Belaying partner ensures safety.";
//     wordHintsMedium["wrestling"] = "Pins and submissions score points.";
//     wordHintsMedium["diving"] = "Judges score on form and difficulty.";
//     wordHintsMedium["sailing"] = "Tacking against the wind to progress.";
//     wordHintsMedium["gymnastics"] = "Floor, vault, bars, and beam events.";

//     // Countries
//     wordHintsMedium["india"] = "Second most populous nation on Earth.";
//     wordHintsMedium["japan"] = "Island nation with bullet trains.";
//     wordHintsMedium["brazil"] = "Largest South American country.";
//     wordHintsMedium["kenya"] = "Rift Valley runs through middle.";
//     wordHintsMedium["france"] = "Hexagon-shaped European nation.";
//     wordHintsMedium["canada"] = "Second largest country by area.";
//     wordHintsMedium["germany"] = "Heart of Europe, reunified in 1990.";
//     wordHintsMedium["china"] = "Most populous country in the world.";
//     wordHintsMedium["italy"] = "Boot-shaped peninsula in Mediterranean.";
//     wordHintsMedium["spain"] = "Iberian peninsula, speaks Castilian.";
//     wordHintsMedium["russia"] = "Spans eleven time zones.";
//     wordHintsMedium["mexico"] = "Aztec and Mayan civilizations originated here.";
//     wordHintsMedium["australia"] = "Continent and country combined.";
//     wordHintsMedium["turkey"] = "Istanbul straddles two continents.";
//     wordHintsMedium["norway"] = "Midnight sun in summer months.";
//     wordHintsMedium["sweden"] = "Nobel Prize ceremonies held here.";
//     wordHintsMedium["greece"] = "Olympic Games originated here.";
//     wordHintsMedium["argentina"] = "Second largest South American nation.";
//     wordHintsMedium["chile"] = "Atacama Desert is world's driest.";
//     wordHintsMedium["egypt"] = "Nile River flows north through it.";
//     wordHintsMedium["nigeria"] = "Nollywood film industry located here.";
//     wordHintsMedium["thailand"] = "Never colonized by European powers.";
//     wordHintsMedium["indonesia"] = "Over 17,000 islands in archipelago.";
//     wordHintsMedium["vietnam"] = "S-shaped country in Southeast Asia.";
//     wordHintsMedium["portugal"] = "Age of Exploration started here.";

//     // === HARD HINTS (Cryptic riddles and wordplay) ===
//     // Animals
//     wordHintsHard["cat"] = "Feline that might be curious about satisfaction.";
//     wordHintsHard["lion"] = "Maned monarch of African savanna.";
//     wordHintsHard["penguin"] = "Tuxedoed Antarctic resident.";
//     wordHintsHard["elephant"] = "Memory keeper with ivory tusks.";
//     wordHintsHard["zebra"] = "Black and white but read all over?";
//     wordHintsHard["giraffe"] = "Neck and neck with the sky.";
//     wordHintsHard["kangaroo"] = "Boxing marsupial from down under.";
//     wordHintsHard["tiger"] = "Burning bright in forests of night.";
//     wordHintsHard["bear"] = "Market crasher or honey lover?";
//     wordHintsHard["wolf"] = "Huffs and puffs but house stands firm.";
//     wordHintsHard["fox"] = "Sly character in Aesop's tales.";
//     wordHintsHard["monkey"] = "See no evil, hear no evil, speak no evil.";
//     wordHintsHard["rabbit"] = "Alice's guide to wonderland.";
//     wordHintsHard["panda"] = "China's diplomatic gift in black and white.";
//     wordHintsHard["whale"] = "Jonah's temporary accommodation.";
//     wordHintsHard["shark"] = "Week dedicated to this predator on TV.";
//     wordHintsHard["eagle"] = "American symbol that soars high.";
//     wordHintsHard["owl"] = "Wise nocturnal mail carrier in Harry Potter.";
//     wordHintsHard["dolphin"] = "Flipper's species, clicks and whistles.";
//     wordHintsHard["leopard"] = "Spots that never change?";
//     wordHintsHard["hippo"] = "River horse in Greek translation.";
//     wordHintsHard["rhino"] = "Horned heavyweight of Africa.";
//     wordHintsHard["deer"] = "Bambi's species in the forest.";
//     wordHintsHard["cheetah"] = "Cheats at speed but fair in heart.";
//     wordHintsHard["squirrel"] = "Nutty neighbor in your backyard.";

//     // Food
//     wordHintsHard["pizza"] = "Italian disc topped with dreams.";
//     wordHintsHard["pasta"] = "Italian tubes, strings, and shells.";
//     wordHintsHard["samosa"] = "Triangular treasure from India.";
//     wordHintsHard["biryani"] = "Aromatic rice palace of spices.";
//     wordHintsHard["waffle"] = "Breakfast grid that holds syrup.";
//     wordHintsHard["burger"] = "Bun sandwich that conquered the world.";
//     wordHintsHard["noodles"] = "Slurp-worthy strands from the East.";
//     wordHintsHard["salad"] = "Garden's gift tossed together.";
//     wordHintsHard["cheese"] = "Milk's transformation through time.";
//     wordHintsHard["steak"] = "Cow's contribution to fine dining.";
//     wordHintsHard["omelette"] = "Egg's folded French expression.";
//     wordHintsHard["pancake"] = "Flat cake that stacks high.";
//     wordHintsHard["bacon"] = "Pig's crispy morning offering.";
//     wordHintsHard["sausage"] = "Meat wrapped in its own casing.";
//     wordHintsHard["donut"] = "Sweet ring with a hole story.";
//     wordHintsHard["cookie"] = "Jar's most wanted resident.";
//     wordHintsHard["curry"] = "Spiced stew that warms the soul.";
//     wordHintsHard["sandwich"] = "Earl's invention between bread.";
//     wordHintsHard["soup"] = "Liquid comfort in a bowl.";
//     wordHintsHard["lasagna"] = "Italian layers of pasta perfection.";
//     wordHintsHard["dumpling"] = "Pocket of flavor wrapped tight.";
//     wordHintsHard["kebab"] = "Skewered meat over open flames.";
//     wordHintsHard["toast"] = "Bread's heated transformation.";
//     wordHintsHard["fries"] = "Potato strips that conquered fast food.";
//     wordHintsHard["risotto"] = "Italian rice dish stirred with love.";

//     // Movies
//     wordHintsHard["titanic"] = "Unsinkable ship's tragic maiden voyage.";
//     wordHintsHard["inception"] = "Dreams layered like Russian dolls.";
//     wordHintsHard["joker"] = "Clown prince of Gotham's chaos.";
//     wordHintsHard["frozen"] = "Ice queen's journey to self-acceptance.";
//     wordHintsHard["avatar"] = "Blue beings versus human greed.";
//     wordHintsHard["gladiator"] = "Roman arena echoes with revenge.";
//     wordHintsHard["shrek"] = "Ogre's tale of true love's layers.";
//     wordHintsHard["matrix"] = "Red pill reveals artificial reality.";
//     wordHintsHard["coco"] = "Music bridges life and death.";
//     wordHintsHard["up"] = "Balloons lift house and heart.";
//     wordHintsHard["batman"] = "Dark knight's war on crime.";
//     wordHintsHard["superman"] = "Last son of Krypton saves Earth.";
//     wordHintsHard["psycho"] = "Motel shower scene terrifies still.";
//     wordHintsHard["notebook"] = "Love story written on pages.";
//     wordHintsHard["memento"] = "Backward tale of forward amnesia.";
//     wordHintsHard["aladdin"] = "Street rat's magical carpet ride.";
//     wordHintsHard["gravity"] = "Space debris threatens astronauts.";
//     wordHintsHard["jaws"] = "Great white terrorizes beach town.";
//     wordHintsHard["rocky"] = "Italian Stallion goes the distance.";
//     wordHintsHard["casablanca"] = "Wartime romance in Moroccan city.";
//     wordHintsHard["interstellar"] = "Love transcends space and time.";
//     wordHintsHard["tenet"] = "Palindrome of time inversion.";
//     wordHintsHard["dune"] = "Desert planet's spice controls universe.";
//     wordHintsHard["zootopia"] = "Animal metropolis tackles prejudice.";
//     wordHintsHard["moana"] = "Ocean calls island girl to voyage.";

//     // Sports
//     wordHintsHard["cricket"] = "Gentlemen's game with tea breaks.";
//     wordHintsHard["tennis"] = "Love-love could mean a tie.";
//     wordHintsHard["boxing"] = "Sweet science of controlled violence.";
//     wordHintsHard["karate"] = "Empty hand way of the warrior.";
//     wordHintsHard["skiing"] = "Downhill race against gravity.";
//     wordHintsHard["soccer"] = "Beautiful game played with feet.";
//     wordHintsHard["golf"] = "Walk spoiled by little white ball.";
//     wordHintsHard["rugby"] = "Football played by gentlemen with hands.";
//     wordHintsHard["hockey"] = "Fastest game on ice or grass.";
//     wordHintsHard["cycling"] = "Two wheels spinning towards finish.";
//     wordHintsHard["swimming"] = "Human fish racing through water.";
//     wordHintsHard["badminton"] = "Shuttlecock flies over net divide.";
//     wordHintsHard["volleyball"] = "Six players spike and dig glory.";
//     wordHintsHard["surfing"] = "Riding liquid mountains of the sea.";
//     wordHintsHard["archery"] = "Ancient hunting meets modern precision.";
//     wordHintsHard["fencing"] = "Swordplay with electric scoring.";
//     wordHintsHard["rowing"] = "Backwards motion propels forward.";
//     wordHintsHard["skating"] = "Gliding poetry on frozen stage.";
//     wordHintsHard["baseball"] = "America's pastime of diamond dreams.";
//     wordHintsHard["basketball"] = "Orange sphere meets iron rim.";
//     wordHintsHard["climbing"] = "Vertical dance with rock face.";
//     wordHintsHard["wrestling"] = "Ancient combat of strength and skill.";
//     wordHintsHard["diving"] = "Gravity-defying water entry art.";
//     wordHintsHard["sailing"] = "Harnessing wind to chase horizon.";
//     wordHintsHard["gymnastics"] = "Human body defies natural limits.";

//     // Countries
//     wordHintsHard["india"] = "Subcontinent of spices and software.";
//     wordHintsHard["japan"] = "Rising sun over ancient traditions.";
//     wordHintsHard["brazil"] = "Carnival nation of coffee and soccer.";
//     wordHintsHard["kenya"] = "Safari homeland of marathon champions.";
//     wordHintsHard["france"] = "Hexagonal republic of wine and cheese.";
//     wordHintsHard["canada"] = "Great white north of maple leaves.";
//     wordHintsHard["germany"] = "Engine of Europe's economic power.";
//     wordHintsHard["china"] = "Middle kingdom of ancient wisdom.";
//     wordHintsHard["italy"] = "Boot that kicks Mediterranean style.";
//     wordHintsHard["spain"] = "Iberian passion of flamenco fire.";
//     wordHintsHard["russia"] = "Bear that spans two continents.";
//     wordHintsHard["mexico"] = "Aztec gold meets modern dreams.";
//     wordHintsHard["australia"] = "Island continent down under.";
//     wordHintsHard["turkey"] = "Bridge between East and West.";
//     wordHintsHard["norway"] = "Viking homeland of midnight sun.";
//     wordHintsHard["sweden"] = "Nordic kingdom of innovation.";
//     wordHintsHard["greece"] = "Cradle where democracy was born.";
//     wordHintsHard["argentina"] = "Tango nation of beef and wine.";
//     wordHintsHard["chile"] = "Narrow ribbon along Pacific edge.";
//     wordHintsHard["egypt"] = "Pharaoh's gift beside the Nile.";
//     wordHintsHard["nigeria"] = "Giant of Africa's beating heart.";
//     wordHintsHard["thailand"] = "Land of smiles and golden temples.";
//     wordHintsHard["indonesia"] = "Emerald archipelago of thousands isles.";
//     wordHintsHard["vietnam"] = "Dragon's tail in Southeast Asia.";
//     wordHintsHard["portugal"] = "Navigator nation that explored worlds.";
// }

// void Hangman::drawWord() {
//     int y = (LINES - 16) / 2, x = (COLS - 62) / 2;
//     attron(A_BOLD);
//     mvprintw(y + 7, x + 18, "Word:");
//     attroff(A_BOLD);
//     for (size_t i = 0; i < displayWord.size(); ++i) {
//         mvaddch(y + 7, x + 24 + i * 2, displayWord[i]);
//     }
    
//     // Display appropriate hint based on difficulty level
//     std::string hint;
//     if (difficulty == 1 && wordHintsEasy.count(secretWord)) {
//         hint = "Easy Hint: " + wordHintsEasy[secretWord];
//     } else if (difficulty == 2 && wordHintsMedium.count(secretWord)) {
//         hint = "Medium Clue: " + wordHintsMedium[secretWord];
//     } else if (difficulty == 3 && wordHintsHard.count(secretWord)) {
//         hint = "Hard Riddle: " + wordHintsHard[secretWord];
//     }
    
//     if (!hint.empty()) {
//         attron(COLOR_PAIR(6));
//         // Word wrap long hints
//         if (hint.length() > 60) {
//             std::string line1 = hint.substr(0, 60);
//             std::string line2 = hint.substr(60);
//             mvprintw(y + 9, x + 18, "%s", line1.c_str());
//             mvprintw(y + 10, x + 18, "%s", line2.c_str());
//         } else {
//             mvprintw(y + 9, x + 18, "%s", hint.c_str());
//         }
//         attroff(COLOR_PAIR(6));
//     }
// }

// void Hangman::startGame() {
//     gameOver = false;
//     wrongGuesses = 0;
//     guessedLetters.clear();

//     // Select random category and word
//     auto categoryIt = sessionCategories.begin();
//     std::advance(categoryIt, rand() % sessionCategories.size());
//     currentCategory = categoryIt->first;

//     const auto& words = categoryIt->second;
//     secretWord = words[rand() % words.size()];
//     displayWord = std::string(secretWord.length(), '_');

//     // === Main Game Loop ===
//     while (!gameOver) {
//         clear();
//         attron(COLOR_PAIR(5));
//         box(stdscr, 0, 0);
//         mvprintw(1, 2, "== Hangman ==");
//         mvprintw(3, 2, "Category: %s", currentCategory.c_str());

//         // Guessed letters
//         mvprintw(5, 2, "Guessed Letters: ");
//         for (char ch : guessedLetters)
//             printw("%c ", ch);

//         // Wrong guesses
//         mvprintw(6, 2, "Wrong Guesses: %d / 6", wrongGuesses);

//         // Draw the word and hint
//         drawWord();

//         refresh();

//         // Handle input
//         int ch = getch();
//         if (std::isalpha(ch)) {
//             makeGuess(static_cast<char>(std::tolower(ch)));
//         } else if (ch == 27) { // ESC key to quit early
//             break;
//         }

//         // Show result if game over
//         if (isGameOver()) {
//             clear();
//             attron(COLOR_PAIR(hasWon() ? 7 : 6));
//             mvprintw(10, 10, hasWon() ? "🎉 You Won!" : "💀 You Lost!");
//             mvprintw(12, 10, "Word was: %s", secretWord.c_str());
//             mvprintw(14, 10, "Press any key to return...");
//             attroff(COLOR_PAIR(hasWon() ? 7 : 6));
//             refresh();
//             getch();
//         }
//     }
// }


// bool Hangman::makeGuess(char letter) {
//     letter = std::tolower(letter);
    
//     // Check if already guessed
//     if (guessedLetters.find(letter) != guessedLetters.end()) {
//         return false;
//     }
    
//     guessedLetters.insert(letter);
    
//     bool found = false;
//     for (size_t i = 0; i < secretWord.length(); ++i) {
//         if (secretWord[i] == letter) {
//             displayWord[i] = letter;
//             found = true;
//         }
//     }
    
//     if (!found) {
//         wrongGuesses++;
//     }
    
//     // Check win condition
//     if (displayWord == secretWord) {
//         gameOver = true;
//         // Award points based on difficulty
//         int points = (difficulty == 1) ? 10 : (difficulty == 2) ? 20 : 30;
//         score += points;
//         return true;
//     }
    
//     // Check lose condition
//     if (wrongGuesses >= 6) {
//         gameOver = true;
//     }
    
//     return found;
// }

// bool Hangman::isGameOver() const {
//     return gameOver;
// }

// bool Hangman::hasWon() const {
//     return gameOver && (displayWord == secretWord);
// }

// int Hangman::getWrongGuesses() const {
//     return wrongGuesses;
// }

// std::string Hangman::getSecretWord() const {
//     return secretWord;
// }

// std::string Hangman::getDisplayWord() const {
//     return displayWord;
// }

// std::string Hangman::getCurrentCategory() const {
//     return currentCategory;
// }

// std::set<char> Hangman::getGuessedLetters() const {
//     return guessedLetters;
// }

// int Hangman::getScore() const {
//     return score;
// }

// void Hangman::resetScore() {
//     score = 0;
// }
// hangman.cpp

#include "hangman.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <ncurses.h>
#include <algorithm>

Hangman::Hangman() : difficulty(1), gameOver(false), wrongGuesses(0), score(0) {
    srand(static_cast<unsigned int>(time(0)));
    loadWords();
    currentCategory = "Animals";
    sessionCategories = categories;
}

Hangman::~Hangman() {}

void Hangman::setDifficulty(int d) {
    if (d >= 1 && d <= 3)
        difficulty = d;
    else
        difficulty = 1; // default to easy if invalid
}

void Hangman::loadWords() {
    categories.clear();

    // Populate categories with words (same as detailed in [1])
    categories["Animals"] = {"cat", "lion", "penguin", "elephant", "zebra", "giraffe", "kangaroo", "tiger", "bear", "wolf", "fox", "monkey", "rabbit", "panda", "whale", "shark", "eagle", "owl", "dolphin", "leopard", "hippo", "rhino", "deer", "cheetah", "squirrel"};
    categories["Food"] = {"pizza", "pasta", "samosa", "biryani", "waffle", "burger", "noodles", "salad", "cheese", "steak", "omelette", "pancake", "bacon", "sausage", "donut", "cookie", "curry", "sandwich", "soup", "lasagna", "dumpling", "kebab", "toast", "fries", "risotto"};
    categories["Movies"] = {"titanic", "inception", "joker", "frozen", "avatar", "gladiator", "shrek", "matrix", "coco", "up", "batman", "superman", "psycho", "notebook", "memento", "aladdin", "gravity", "jaws", "rocky", "casablanca", "interstellar", "tenet", "dune", "zootopia", "moana"};
    categories["Sports"] = {"cricket", "tennis", "boxing", "karate", "skiing", "soccer", "golf", "rugby", "hockey", "cycling", "swimming", "badminton", "volleyball", "surfing", "archery", "fencing", "rowing", "skating", "baseball", "basketball", "climbing", "wrestling", "diving", "sailing", "gymnastics"};
    categories["Countries"] = {"india", "japan", "brazil", "kenya", "france", "canada", "germany", "china", "italy", "spain", "russia", "mexico", "australia", "turkey", "norway", "sweden", "greece", "argentina", "chile", "egypt", "nigeria", "thailand", "indonesia", "vietnam", "portugal"};
    sessionCategories = categories;
    // Load hints for all difficulties (easy, medium, hard) - as provided in detail in [1]
    wordHintsEasy.clear();
    wordHintsMedium.clear();
    wordHintsHard.clear();

    wordHintsEasy["cat"] = "A small domesticated feline animal.";
    wordHintsEasy["lion"] = "King of the jungle with a mane.";
    wordHintsEasy["penguin"] = "A flightless bird often seen in Antarctica.";
    wordHintsEasy["elephant"] = "The largest land animal.";
    wordHintsEasy["zebra"] = "Horse-like animal with black-and-white stripes.";
    wordHintsEasy["giraffe"] = "The tallest living terrestrial animal.";
    wordHintsEasy["kangaroo"] = "Australian marsupial that hops.";
    wordHintsEasy["tiger"] = "Striped big cat, predator.";
    wordHintsEasy["bear"] = "Large mammal known for hibernation.";
    wordHintsEasy["wolf"] = "Wild ancestor of the domestic dog.";
    wordHintsEasy["fox"] = "A clever red-furred animal.";
    wordHintsEasy["monkey"] = "Primates that love swinging from trees.";
    wordHintsEasy["rabbit"] = "Furry animal with long ears.";
    wordHintsEasy["panda"] = "Black-and-white bear that eats bamboo.";
    wordHintsEasy["whale"] = "Huge ocean-dwelling mammal.";
    wordHintsEasy["shark"] = "Predator fish with sharp teeth.";
    wordHintsEasy["eagle"] = "A majestic bird of prey.";
    wordHintsEasy["owl"] = "Nocturnal bird that hoots.";
    wordHintsEasy["dolphin"] = "Intelligent marine mammal.";
    wordHintsEasy["leopard"] = "Spotted wild feline predator.";
    wordHintsEasy["hippo"] = "Huge semi-aquatic African mammal.";
    wordHintsEasy["rhino"] = "Large mammal with horns.";
    wordHintsEasy["deer"] = "Forest animal with antlers.";
    wordHintsEasy["cheetah"] = "Fastest land animal.";
    wordHintsEasy["squirrel"] = "Tree climber that gathers nuts.";

    // Food
    wordHintsEasy["pizza"] = "Italian dish with toppings on dough.";
    wordHintsEasy["pasta"] = "Italian noodles in many shapes.";
    wordHintsEasy["samosa"] = "Fried triangular Indian snack.";
    wordHintsEasy["biryani"] = "Fragrant rice dish with spices.";
    wordHintsEasy["waffle"] = "Grid-patterned breakfast cake.";
    wordHintsEasy["burger"] = "A sandwich with a meat patty.";
    wordHintsEasy["noodles"] = "Long strands of pasta or ramen.";
    wordHintsEasy["salad"] = "Mix of veggies, sometimes with dressing.";
    wordHintsEasy["cheese"] = "Dairy product, often yellow or white.";
    wordHintsEasy["steak"] = "Grilled or pan-fried meat slice.";
    wordHintsEasy["omelette"] = "Cooked eggs folded with fillings.";
    wordHintsEasy["pancake"] = "Flat breakfast cake.";
    wordHintsEasy["bacon"] = "Crispy meat strips from pigs.";
    wordHintsEasy["sausage"] = "Ground meat in a casing.";
    wordHintsEasy["donut"] = "Sweet fried ring-shaped treat.";
    wordHintsEasy["cookie"] = "Small sweet baked dessert.";
    wordHintsEasy["curry"] = "Spicy stew often from India.";
    wordHintsEasy["sandwich"] = "Bread with fillings in between.";
    wordHintsEasy["soup"] = "Warm liquid dish.";
    wordHintsEasy["lasagna"] = "Layered pasta dish with cheese.";
    wordHintsEasy["dumpling"] = "Stuffed dough cooked by boiling or frying.";
    wordHintsEasy["kebab"] = "Grilled meat on a skewer.";
    wordHintsEasy["toast"] = "Bread browned by heat.";
    wordHintsEasy["fries"] = "Thin sticks of fried potato.";
    wordHintsEasy["risotto"] = "Creamy Italian rice dish.";

    // Movies
    wordHintsEasy["titanic"] = "Ship disaster romance with DiCaprio.";
    wordHintsEasy["inception"] = "Dreams within dreams thriller.";
    wordHintsEasy["joker"] = "Batman's arch-nemesis origin story.";
    wordHintsEasy["frozen"] = "Disney movie about ice powers.";
    wordHintsEasy["avatar"] = "Blue aliens on Pandora.";
    wordHintsEasy["gladiator"] = "Roman warrior who fought for sport.";
    wordHintsEasy["shrek"] = "Green ogre who lives in a swamp.";
    wordHintsEasy["matrix"] = "Neo discovers a virtual reality.";
    wordHintsEasy["coco"] = "A Pixar film about music and memory.";
    wordHintsEasy["up"] = "An old man flies with balloons.";
    wordHintsEasy["batman"] = "Masked vigilante of Gotham.";
    wordHintsEasy["superman"] = "Alien hero from Krypton.";
    wordHintsEasy["psycho"] = "Horror movie by Alfred Hitchcock.";
    wordHintsEasy["notebook"] = "Romantic movie based on a novel.";
    wordHintsEasy["memento"] = "Story told backward about memory loss.";
    wordHintsEasy["aladdin"] = "Street boy with a magic lamp.";
    wordHintsEasy["gravity"] = "Two astronauts stuck in space.";
    wordHintsEasy["jaws"] = "Movie about a killer shark.";
    wordHintsEasy["rocky"] = "Boxer's underdog story.";
    wordHintsEasy["casablanca"] = "Classic romantic film during war.";
    wordHintsEasy["interstellar"] = "Time-bending space exploration film.";
    wordHintsEasy["tenet"] = "Action thriller with time inversion.";
    wordHintsEasy["dune"] = "Sci-fi movie set on Arrakis.";
    wordHintsEasy["zootopia"] = "Animated city of talking animals.";
    wordHintsEasy["moana"] = "Island girl sails to save the world.";

    // Sports
    wordHintsEasy["cricket"] = "Bat and ball sport popular in England.";
    wordHintsEasy["tennis"] = "Racket sport with a net.";
    wordHintsEasy["boxing"] = "Fighting sport using gloves.";
    wordHintsEasy["karate"] = "Japanese martial art.";
    wordHintsEasy["skiing"] = "Snow sport using skis.";
    wordHintsEasy["soccer"] = "Football played around the world.";
    wordHintsEasy["golf"] = "Sport with clubs and holes.";
    wordHintsEasy["rugby"] = "Contact sport similar to football.";
    wordHintsEasy["hockey"] = "Ice or field team sport.";
    wordHintsEasy["cycling"] = "Sport using a bicycle.";
    wordHintsEasy["swimming"] = "Moving in water for sport.";
    wordHintsEasy["badminton"] = "Racquet game with a shuttlecock.";
    wordHintsEasy["volleyball"] = "Game with a ball over a net.";
    wordHintsEasy["surfing"] = "Riding ocean waves on a board.";
    wordHintsEasy["archery"] = "Shooting arrows with a bow.";
    wordHintsEasy["fencing"] = "Sword-fighting sport.";
    wordHintsEasy["rowing"] = "Team boat racing with oars.";
    wordHintsEasy["skating"] = "Gliding on wheels or blades.";
    wordHintsEasy["baseball"] = "American bat-and-ball sport.";
    wordHintsEasy["basketball"] = "Game of hoops and dribbles.";
    wordHintsEasy["climbing"] = "Ascending rocks or walls.";
    wordHintsEasy["wrestling"] = "Grappling combat sport.";
    wordHintsEasy["diving"] = "Jumping into water gracefully.";
    wordHintsEasy["sailing"] = "Using wind to power boats.";
    wordHintsEasy["gymnastics"] = "Acrobatic sport with routines.";

    // Countries
    wordHintsEasy["india"] = "Bollywood and curry homeland.";
    wordHintsEasy["japan"] = "Land of the rising sun.";
    wordHintsEasy["brazil"] = "Famous for football and carnival.";
    wordHintsEasy["kenya"] = "Known for wildlife and runners.";
    wordHintsEasy["france"] = "Eiffel Tower and croissants.";
    wordHintsEasy["canada"] = "Land of maple syrup.";
    wordHintsEasy["germany"] = "Famous for engineering and Oktoberfest.";
    wordHintsEasy["china"] = "Great Wall and fast tech.";
    wordHintsEasy["italy"] = "Pizza, pasta, and Rome.";
    wordHintsEasy["spain"] = "Flamenco and fiestas.";
    wordHintsEasy["russia"] = "Largest country in the world.";
    wordHintsEasy["mexico"] = "Home of tacos and Aztecs.";
    wordHintsEasy["australia"] = "Kangaroos and the outback.";
    wordHintsEasy["turkey"] = "Bridges Europe and Asia.";
    wordHintsEasy["norway"] = "Land of fjords.";
    wordHintsEasy["sweden"] = "Home of ABBA and IKEA.";
    wordHintsEasy["greece"] = "Cradle of western civilization.";
    wordHintsEasy["argentina"] = "Famous for tango and Messi.";
    wordHintsEasy["chile"] = "Long coastal nation of South America.";
    wordHintsEasy["egypt"] = "Pyramids and ancient history.";
    wordHintsEasy["nigeria"] = "Most populous African nation.";
    wordHintsEasy["thailand"] = "Known for beaches and cuisine.";
    wordHintsEasy["indonesia"] = "Archipelago nation with many islands.";
    wordHintsEasy["vietnam"] = "Pho and historical wars.";
    wordHintsEasy["portugal"] = "Lisbon and custard tarts.";

    // === MEDIUM HINTS (Clues and characteristics) ===
    // Animals
    wordHintsMedium["cat"] = "Purrs when content, has retractable claws.";
    wordHintsMedium["lion"] = "Lives in prides, roars loudly.";
    wordHintsMedium["penguin"] = "Waddles on ice, excellent swimmer.";
    wordHintsMedium["elephant"] = "Never forgets, has a trunk.";
    wordHintsMedium["zebra"] = "No two have identical patterns.";
    wordHintsMedium["giraffe"] = "Purple tongue, ossicones on head.";
    wordHintsMedium["kangaroo"] = "Carries babies in a pouch.";
    wordHintsMedium["tiger"] = "Solitary hunter, orange and black.";
    wordHintsMedium["bear"] = "Sleeps through winter months.";
    wordHintsMedium["wolf"] = "Travels in packs, howls at moon.";
    wordHintsMedium["fox"] = "Bushy tail, cunning reputation.";
    wordHintsMedium["monkey"] = "Opposable thumbs, social creatures.";
    wordHintsMedium["rabbit"] = "Thumps hind legs when scared.";
    wordHintsMedium["panda"] = "Endangered Chinese bear species.";
    wordHintsMedium["whale"] = "Communicates through songs.";
    wordHintsMedium["shark"] = "Cartilaginous skeleton, multiple rows of teeth.";
    wordHintsMedium["eagle"] = "National bird of several countries.";
    wordHintsMedium["owl"] = "Can turn head 270 degrees.";
    wordHintsMedium["dolphin"] = "Echolocation for navigation.";
    wordHintsMedium["leopard"] = "Excellent climber, nocturnal hunter.";
    wordHintsMedium["hippo"] = "Spends most day in water.";
    wordHintsMedium["rhino"] = "Poor eyesight, excellent hearing.";
    wordHintsMedium["deer"] = "Males shed antlers annually.";
    wordHintsMedium["cheetah"] = "Can't roar, only chirps and purrs.";
    wordHintsMedium["squirrel"] = "Buries nuts for winter storage.";

    // Food
    wordHintsMedium["pizza"] = "Originated in Naples, Italy.";
    wordHintsMedium["pasta"] = "Made from durum wheat semolina.";
    wordHintsMedium["samosa"] = "Often filled with potatoes and peas.";
    wordHintsMedium["biryani"] = "Layered rice dish with saffron.";
    wordHintsMedium["waffle"] = "Cooked in a special iron press.";
    wordHintsMedium["burger"] = "Often served with lettuce and tomato.";
    wordHintsMedium["noodles"] = "Can be made from rice or wheat.";
    wordHintsMedium["salad"] = "Often dressed with oil and vinegar.";
    wordHintsMedium["cheese"] = "Aged varieties have stronger flavors.";
    wordHintsMedium["steak"] = "Cooking levels from rare to well-done.";
    wordHintsMedium["omelette"] = "French technique, beaten eggs folded.";
    wordHintsMedium["pancake"] = "Leavened with baking powder or soda.";
    wordHintsMedium["bacon"] = "Cured and smoked pork belly.";
    wordHintsMedium["sausage"] = "Often seasoned with herbs and spices.";
    wordHintsMedium["donut"] = "Deep-fried in oil, often glazed.";
    wordHintsMedium["cookie"] = "Can be soft-baked or crispy.";
    wordHintsMedium["curry"] = "Uses blend of ground spices.";
    wordHintsMedium["sandwich"] = "Named after Earl of Sandwich.";
    wordHintsMedium["soup"] = "Can be served hot or cold.";
    wordHintsMedium["lasagna"] = "Baked pasta dish with bechamel.";
    wordHintsMedium["dumpling"] = "Wrapper can be steamed or fried.";
    wordHintsMedium["kebab"] = "Meat marinated before grilling.";
    wordHintsMedium["toast"] = "Maillard reaction creates browning.";
    wordHintsMedium["fries"] = "Twice-cooked for extra crispiness.";
    wordHintsMedium["risotto"] = "Stirred constantly while cooking.";

    // Movies
    wordHintsMedium["titanic"] = "1997 disaster romance, 11 Oscars.";
    wordHintsMedium["inception"] = "Christopher Nolan's dream heist.";
    wordHintsMedium["joker"] = "Joaquin Phoenix won Oscar for role.";
    wordHintsMedium["frozen"] = "Let it go, let it go...";
    wordHintsMedium["avatar"] = "Highest-grossing film for a decade.";
    wordHintsMedium["gladiator"] = "Are you not entertained?";
    wordHintsMedium["shrek"] = "Mike Myers voices green protagonist.";
    wordHintsMedium["matrix"] = "Choose the red or blue pill.";
    wordHintsMedium["coco"] = "Remember me, though I have to travel far.";
    wordHintsMedium["up"] = "Adventure is out there!";
    wordHintsMedium["batman"] = "I'm not wearing hockey pads.";
    wordHintsMedium["superman"] = "Faster than a speeding bullet.";
    wordHintsMedium["psycho"] = "Shower scene is iconic.";
    wordHintsMedium["notebook"] = "If you're a bird, I'm a bird.";
    wordHintsMedium["memento"] = "Guy Pearce has memory issues.";
    wordHintsMedium["aladdin"] = "A whole new world awaits.";
    wordHintsMedium["gravity"] = "Sandra Bullock in space debris.";
    wordHintsMedium["jaws"] = "You're gonna need a bigger boat.";
    wordHintsMedium["rocky"] = "Going the distance with Apollo.";
    wordHintsMedium["casablanca"] = "Here's looking at you, kid.";
    wordHintsMedium["interstellar"] = "Love transcends dimensions.";
    wordHintsMedium["tenet"] = "Don't try to understand it, feel it.";
    wordHintsMedium["dune"] = "The spice must flow on desert planet.";
    wordHintsMedium["zootopia"] = "Anyone can be anything in this city.";
    wordHintsMedium["moana"] = "The ocean chose her for a quest.";

    // Sports
    wordHintsMedium["cricket"] = "Played with wickets and overs.";
    wordHintsMedium["tennis"] = "Love means zero in scoring.";
    wordHintsMedium["boxing"] = "Sweet science of hit and don't get hit.";
    wordHintsMedium["karate"] = "Empty hand fighting technique.";
    wordHintsMedium["skiing"] = "Downhill or cross-country variants.";
    wordHintsMedium["soccer"] = "90 minutes plus injury time.";
    wordHintsMedium["golf"] = "Par is the standard score.";
    wordHintsMedium["rugby"] = "15 players per side in union.";
    wordHintsMedium["hockey"] = "Puck or ball depending on surface.";
    wordHintsMedium["cycling"] = "Peloton rides together in races.";
    wordHintsMedium["swimming"] = "Four main strokes in competition.";
    wordHintsMedium["badminton"] = "Shuttlecock made from feathers.";
    wordHintsMedium["volleyball"] = "Six players per side, net height matters.";
    wordHintsMedium["surfing"] = "Pipeline and barrel are famous moves.";
    wordHintsMedium["archery"] = "Robin Hood was legendary at this.";
    wordHintsMedium["fencing"] = "Foil, epee, and sabre are weapons.";
    wordHintsMedium["rowing"] = "Crew sport with coxswain calling rhythm.";
    wordHintsMedium["skating"] = "Figure or speed variants exist.";
    wordHintsMedium["baseball"] = "Nine innings, three strikes you're out.";
    wordHintsMedium["basketball"] = "Invented by James Naismith in 1891.";
    wordHintsMedium["climbing"] = "Belaying partner ensures safety.";
    wordHintsMedium["wrestling"] = "Pins and submissions score points.";
    wordHintsMedium["diving"] = "Judges score on form and difficulty.";
    wordHintsMedium["sailing"] = "Tacking against the wind to progress.";
    wordHintsMedium["gymnastics"] = "Floor, vault, bars, and beam events.";

    // Countries
    wordHintsMedium["india"] = "Second most populous nation on Earth.";
    wordHintsMedium["japan"] = "Island nation with bullet trains.";
    wordHintsMedium["brazil"] = "Largest South American country.";
    wordHintsMedium["kenya"] = "Rift Valley runs through middle.";
    wordHintsMedium["france"] = "Hexagon-shaped European nation.";
    wordHintsMedium["canada"] = "Second largest country by area.";
    wordHintsMedium["germany"] = "Heart of Europe, reunified in 1990.";
    wordHintsMedium["china"] = "Most populous country in the world.";
    wordHintsMedium["italy"] = "Boot-shaped peninsula in Mediterranean.";
    wordHintsMedium["spain"] = "Iberian peninsula, speaks Castilian.";
    wordHintsMedium["russia"] = "Spans eleven time zones.";
    wordHintsMedium["mexico"] = "Aztec and Mayan civilizations originated here.";
    wordHintsMedium["australia"] = "Continent and country combined.";
    wordHintsMedium["turkey"] = "Istanbul straddles two continents.";
    wordHintsMedium["norway"] = "Midnight sun in summer months.";
    wordHintsMedium["sweden"] = "Nobel Prize ceremonies held here.";
    wordHintsMedium["greece"] = "Olympic Games originated here.";
    wordHintsMedium["argentina"] = "Second largest South American nation.";
    wordHintsMedium["chile"] = "Atacama Desert is world's driest.";
    wordHintsMedium["egypt"] = "Nile River flows north through it.";
    wordHintsMedium["nigeria"] = "Nollywood film industry located here.";
    wordHintsMedium["thailand"] = "Never colonized by European powers.";
    wordHintsMedium["indonesia"] = "Over 17,000 islands in archipelago.";
    wordHintsMedium["vietnam"] = "S-shaped country in Southeast Asia.";
    wordHintsMedium["portugal"] = "Age of Exploration started here.";

    // === HARD HINTS (Cryptic riddles and wordplay) ===
    // Animals
    wordHintsHard["cat"] = "Feline that might be curious about satisfaction.";
    wordHintsHard["lion"] = "Maned monarch of African savanna.";
    wordHintsHard["penguin"] = "Tuxedoed Antarctic resident.";
    wordHintsHard["elephant"] = "Memory keeper with ivory tusks.";
    wordHintsHard["zebra"] = "Black and white but read all over?";
    wordHintsHard["giraffe"] = "Neck and neck with the sky.";
    wordHintsHard["kangaroo"] = "Boxing marsupial from down under.";
    wordHintsHard["tiger"] = "Burning bright in forests of night.";
    wordHintsHard["bear"] = "Market crasher or honey lover?";
    wordHintsHard["wolf"] = "Huffs and puffs but house stands firm.";
    wordHintsHard["fox"] = "Sly character in Aesop's tales.";
    wordHintsHard["monkey"] = "See no evil, hear no evil, speak no evil.";
    wordHintsHard["rabbit"] = "Alice's guide to wonderland.";
    wordHintsHard["panda"] = "China's diplomatic gift in black and white.";
    wordHintsHard["whale"] = "Jonah's temporary accommodation.";
    wordHintsHard["shark"] = "Week dedicated to this predator on TV.";
    wordHintsHard["eagle"] = "American symbol that soars high.";
    wordHintsHard["owl"] = "Wise nocturnal mail carrier in Harry Potter.";
    wordHintsHard["dolphin"] = "Flipper's species, clicks and whistles.";
    wordHintsHard["leopard"] = "Spots that never change?";
    wordHintsHard["hippo"] = "River horse in Greek translation.";
    wordHintsHard["rhino"] = "Horned heavyweight of Africa.";
    wordHintsHard["deer"] = "Bambi's species in the forest.";
    wordHintsHard["cheetah"] = "Cheats at speed but fair in heart.";
    wordHintsHard["squirrel"] = "Nutty neighbor in your backyard.";

    // Food
    wordHintsHard["pizza"] = "Italian disc topped with dreams.";
    wordHintsHard["pasta"] = "Italian tubes, strings, and shells.";
    wordHintsHard["samosa"] = "Triangular treasure from India.";
    wordHintsHard["biryani"] = "Aromatic rice palace of spices.";
    wordHintsHard["waffle"] = "Breakfast grid that holds syrup.";
    wordHintsHard["burger"] = "Bun sandwich that conquered the world.";
    wordHintsHard["noodles"] = "Slurp-worthy strands from the East.";
    wordHintsHard["salad"] = "Garden's gift tossed together.";
    wordHintsHard["cheese"] = "Milk's transformation through time.";
    wordHintsHard["steak"] = "Cow's contribution to fine dining.";
    wordHintsHard["omelette"] = "Egg's folded French expression.";
    wordHintsHard["pancake"] = "Flat cake that stacks high.";
    wordHintsHard["bacon"] = "Pig's crispy morning offering.";
    wordHintsHard["sausage"] = "Meat wrapped in its own casing.";
    wordHintsHard["donut"] = "Sweet ring with a hole story.";
    wordHintsHard["cookie"] = "Jar's most wanted resident.";
    wordHintsHard["curry"] = "Spiced stew that warms the soul.";
    wordHintsHard["sandwich"] = "Earl's invention between bread.";
    wordHintsHard["soup"] = "Liquid comfort in a bowl.";
    wordHintsHard["lasagna"] = "Italian layers of pasta perfection.";
    wordHintsHard["dumpling"] = "Pocket of flavor wrapped tight.";
    wordHintsHard["kebab"] = "Skewered meat over open flames.";
    wordHintsHard["toast"] = "Bread's heated transformation.";
    wordHintsHard["fries"] = "Potato strips that conquered fast food.";
    wordHintsHard["risotto"] = "Italian rice dish stirred with love.";

    // Movies
    wordHintsHard["titanic"] = "Unsinkable ship's tragic maiden voyage.";
    wordHintsHard["inception"] = "Dreams layered like Russian dolls.";
    wordHintsHard["joker"] = "Clown prince of Gotham's chaos.";
    wordHintsHard["frozen"] = "Ice queen's journey to self-acceptance.";
    wordHintsHard["avatar"] = "Blue beings versus human greed.";
    wordHintsHard["gladiator"] = "Roman arena echoes with revenge.";
    wordHintsHard["shrek"] = "Ogre's tale of true love's layers.";
    wordHintsHard["matrix"] = "Red pill reveals artificial reality.";
    wordHintsHard["coco"] = "Music bridges life and death.";
    wordHintsHard["up"] = "Balloons lift house and heart.";
    wordHintsHard["batman"] = "Dark knight's war on crime.";
    wordHintsHard["superman"] = "Last son of Krypton saves Earth.";
    wordHintsHard["psycho"] = "Motel shower scene terrifies still.";
    wordHintsHard["notebook"] = "Love story written on pages.";
    wordHintsHard["memento"] = "Backward tale of forward amnesia.";
    wordHintsHard["aladdin"] = "Street rat's magical carpet ride.";
    wordHintsHard["gravity"] = "Space debris threatens astronauts.";
    wordHintsHard["jaws"] = "Great white terrorizes beach town.";
    wordHintsHard["rocky"] = "Italian Stallion goes the distance.";
    wordHintsHard["casablanca"] = "Wartime romance in Moroccan city.";
    wordHintsHard["interstellar"] = "Love transcends space and time.";
    wordHintsHard["tenet"] = "Palindrome of time inversion.";
    wordHintsHard["dune"] = "Desert planet's spice controls universe.";
    wordHintsHard["zootopia"] = "Animal metropolis tackles prejudice.";
    wordHintsHard["moana"] = "Ocean calls island girl to voyage.";

    // Sports
    wordHintsHard["cricket"] = "Gentlemen's game with tea breaks.";
    wordHintsHard["tennis"] = "Love-love could mean a tie.";
    wordHintsHard["boxing"] = "Sweet science of controlled violence.";
    wordHintsHard["karate"] = "Empty hand way of the warrior.";
    wordHintsHard["skiing"] = "Downhill race against gravity.";
    wordHintsHard["soccer"] = "Beautiful game played with feet.";
    wordHintsHard["golf"] = "Walk spoiled by little white ball.";
    wordHintsHard["rugby"] = "Football played by gentlemen with hands.";
    wordHintsHard["hockey"] = "Fastest game on ice or grass.";
    wordHintsHard["cycling"] = "Two wheels spinning towards finish.";
    wordHintsHard["swimming"] = "Human fish racing through water.";
    wordHintsHard["badminton"] = "Shuttlecock flies over net divide.";
    wordHintsHard["volleyball"] = "Six players spike and dig glory.";
    wordHintsHard["surfing"] = "Riding liquid mountains of the sea.";
    wordHintsHard["archery"] = "Ancient hunting meets modern precision.";
    wordHintsHard["fencing"] = "Swordplay with electric scoring.";
    wordHintsHard["rowing"] = "Backwards motion propels forward.";
    wordHintsHard["skating"] = "Gliding poetry on frozen stage.";
    wordHintsHard["baseball"] = "America's pastime of diamond dreams.";
    wordHintsHard["basketball"] = "Orange sphere meets iron rim.";
    wordHintsHard["climbing"] = "Vertical dance with rock face.";
    wordHintsHard["wrestling"] = "Ancient combat of strength and skill.";
    wordHintsHard["diving"] = "Gravity-defying water entry art.";
    wordHintsHard["sailing"] = "Harnessing wind to chase horizon.";
    wordHintsHard["gymnastics"] = "Human body defies natural limits.";

    // Countries
    wordHintsHard["india"] = "Subcontinent of spices and software.";
    wordHintsHard["japan"] = "Rising sun over ancient traditions.";
    wordHintsHard["brazil"] = "Carnival nation of coffee and soccer.";
    wordHintsHard["kenya"] = "Safari homeland of marathon champions.";
    wordHintsHard["france"] = "Hexagonal republic of wine and cheese.";
    wordHintsHard["canada"] = "Great white north of maple leaves.";
    wordHintsHard["germany"] = "Engine of Europe's economic power.";
    wordHintsHard["china"] = "Middle kingdom of ancient wisdom.";
    wordHintsHard["italy"] = "Boot that kicks Mediterranean style.";
    wordHintsHard["spain"] = "Iberian passion of flamenco fire.";
    wordHintsHard["russia"] = "Bear that spans two continents.";
    wordHintsHard["mexico"] = "Aztec gold meets modern dreams.";
    wordHintsHard["australia"] = "Island continent down under.";
    wordHintsHard["turkey"] = "Bridge between East and West.";
    wordHintsHard["norway"] = "Viking homeland of midnight sun.";
    wordHintsHard["sweden"] = "Nordic kingdom of innovation.";
    wordHintsHard["greece"] = "Cradle where democracy was born.";
    wordHintsHard["argentina"] = "Tango nation of beef and wine.";
    wordHintsHard["chile"] = "Narrow ribbon along Pacific edge.";
    wordHintsHard["egypt"] = "Pharaoh's gift beside the Nile.";
    wordHintsHard["nigeria"] = "Giant of Africa's beating heart.";
    wordHintsHard["thailand"] = "Land of smiles and golden temples.";
    wordHintsHard["indonesia"] = "Emerald archipelago of thousands isles.";
    wordHintsHard["vietnam"] = "Dragon's tail in Southeast Asia.";
    wordHintsHard["portugal"] = "Navigator nation that explored worlds.";
}

void Hangman::selectCategory() {
    clear();
    attron(A_BOLD);
    mvprintw(2, 2, "Select a category by number:");
    attroff(A_BOLD);

    int i = 0;
    std::vector<std::string> catNames;
    for (const auto& cat : categories) {
        mvprintw(4 + i, 4, "%d. %s", i + 1, cat.first.c_str());
        catNames.push_back(cat.first);
        ++i;
    }
    mvprintw(4 + i + 1, 2, "Enter number (1-%d): ", (int)catNames.size());
    refresh();

    echo();
    int choice = 0;
    scanw("%d", &choice);
    noecho();

    if (choice > 0 && choice <= (int)catNames.size()) {
        currentCategory = catNames[choice - 1];
        sessionCategories.clear();
        sessionCategories[currentCategory] = categories[currentCategory];
    } else {
        // Default category if invalid input
        currentCategory = "Animals";
        sessionCategories.clear();
        sessionCategories[currentCategory] = categories[currentCategory];
    }
}

void Hangman::drawHangman() {
    int y = (LINES - 16) / 2;
    int x = (COLS - 62) / 2;

    // Base scaffold always drawn
    mvprintw(y + 1, x + 40, " ______");
    mvprintw(y + 2, x + 40, " |    |");
    
    if (wrongGuesses > 0) mvprintw(y + 3, x + 40, " O");           // head
    if (wrongGuesses > 1) mvprintw(y + 4, x + 40, " |");           // body
    if (wrongGuesses > 2) mvprintw(y + 4, x + 39, "/");           // left arm
    if (wrongGuesses > 3) mvprintw(y + 4, x + 41, "\\");          // right arm
    if (wrongGuesses > 4) mvprintw(y + 5, x + 39, "/");           // left leg
    if (wrongGuesses > 5) mvprintw(y + 5, x + 41, "\\");          // right leg

    mvprintw(y + 6, x + 40, "|");
    mvprintw(y + 7, x + 40, "|");
}

// Draw the secret word with guessed letters and show hint based on difficulty
void Hangman::drawWord() {
    int y = (LINES - 16) / 2, x = (COLS - 62) / 2;
    attron(A_BOLD);
    mvprintw(y + 7, x + 18, "Word: ");
    attroff(A_BOLD);

    for (size_t i = 0; i < displayWord.size(); ++i) {
        mvaddch(y + 7, x + 24 + (int)i * 2, displayWord[i]);
    }

    // Determine hint text by difficulty
    std::string hint;
    if (difficulty == 1 && wordHintsEasy.count(secretWord)) {
        hint = "Easy Hint: " + wordHintsEasy[secretWord];
    }
    else if (difficulty == 2 && wordHintsMedium.count(secretWord)) {
        hint = "Medium Clue: " + wordHintsMedium[secretWord];
    }
    else if (difficulty == 3 && wordHintsHard.count(secretWord)) {
        hint = "Hard Riddle: " + wordHintsHard[secretWord];
    }

    if (!hint.empty()) {
        attron(COLOR_PAIR(6));
        // Word wrap at 60 chars max
        const int wrapLen = 60;
        if ((int)hint.length() > wrapLen) {
            std::string line1 = hint.substr(0, wrapLen);
            std::string line2 = hint.substr(wrapLen);
            mvprintw(y + 9, x + 18, "%s", line1.c_str());
            mvprintw(y + 10, x + 18, "%s", line2.c_str());
        }
        else {
            mvprintw(y + 9, x + 18, "%s", hint.c_str());
        }
        attroff(COLOR_PAIR(6));
    }
}

void Hangman::startGame() {
    selectCategory();

    gameOver = false;
    wrongGuesses = 0;
    guessedLetters.clear();

    // Choose a secret word from selected category
    const auto& words = sessionCategories[currentCategory];
    secretWord = words[rand() % words.size()];
    displayWord = std::string(secretWord.length(), '_');

    while (!gameOver) {
        clear();
        attron(COLOR_PAIR(5));
        box(stdscr, 0, 0);
        attroff(COLOR_PAIR(5));

        mvprintw(1, 2, "== Hangman ==");
        mvprintw(3, 2, "Category: %s", currentCategory.c_str());

        // Guessed letters
        mvprintw(5, 2, "Guessed Letters: ");
        for (char ch : guessedLetters) {
            printw("%c ", ch);
        }

        // Wrong guesses and hangman drawing
        mvprintw(6, 2, "Wrong Guesses: %d / 6", wrongGuesses);
        drawHangman();

        drawWord();

        refresh();

        int ch = getch();
        if (std::isalpha(ch)) {
            makeGuess(std::tolower(ch));
        }
        else if (ch == 27) { // ESC key to quit
            gameOver = true;
            break;
        }

        if (isGameOver()) {
            gameOver = true;
        }
    }

    // Show result
    clear();
    attron(COLOR_PAIR(hasWon() ? 7 : 6));
    mvprintw(10, 10, hasWon() ? " You Won!" : " You Lost!");
    mvprintw(12, 10, "Word was: %s", secretWord.c_str());
    mvprintw(14, 10, "Press any key to return...");
    attroff(COLOR_PAIR(hasWon() ? 7 : 6));
    refresh();
    getch();
}

bool Hangman::makeGuess(char letter) {
    // Ignore if already guessed
    if (guessedLetters.find(letter) != guessedLetters.end())
        return false;

    guessedLetters.insert(letter);
    bool found = false;

    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == letter) {
            displayWord[i] = letter;
            found = true;
        }
    }

    if (!found) {
        wrongGuesses++;
    }

    // Update game state
    if (displayWord == secretWord) {
        gameOver = true;
        int points = (difficulty == 1) ? 10 : (difficulty == 2) ? 20 : 30;
        score += points;
    }
    if (wrongGuesses >= 6) {
        gameOver = true;
    }

    return found;
}

bool Hangman::isGameOver() const {
    return gameOver;
}

bool Hangman::hasWon() const {
    return gameOver && (displayWord == secretWord);
}

int Hangman::getWrongGuesses() const {
    return wrongGuesses;
}

std::string Hangman::getSecretWord() const {
    return secretWord;
}

std::string Hangman::getDisplayWord() const {
    return displayWord;
}

std::string Hangman::getCurrentCategory() const {
    return currentCategory;
}

std::set<char> Hangman::getGuessedLetters() const {
    return guessedLetters;
}

int Hangman::getScore() const {
    return score;
}

void Hangman::resetScore() {
    score = 0;
}
