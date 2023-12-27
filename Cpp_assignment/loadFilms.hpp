#pragma once
#include "film.h"

// Function that instantiates all films to be loaded to the browser.
// Returns a pointer to a vector of const film pointers,
// and pointers are const so that the films cannot be altered
inline std::vector<const film*>* loadFilms() {

	std::vector<const film*>* films = new std::vector<const film*>;

	std::vector<std::string> avatarProtagonists{ "Sam Worthington", "Zoe Saldana", "Sigourney Weaver" };
	std::vector<genre> avatarGenres{ action, adventure, fantasy };
	film* avatar = new film("Avatar", 2009, "James Cameron", avatarProtagonists, avatarGenres, "avatar.png");
	films->push_back(avatar);

	std::vector<std::string> klausProtagonists{ "Jason Schwartzman", "J.K. Simmons", "Rashida Jones" };
	std::vector<genre> klausGenres{ adventure, animation, comedy };
	film* klaus = new film("Klaus", 2019, "Sergio Pablos", klausProtagonists, klausGenres, "klaus.png");
	films->push_back(klaus);

	std::vector<std::string> grandBudapestProtagonists{ "Ralph Fiennes", "F. Murray Abraham", "Tony Revolori" };
	std::vector<genre> grandBudapestGenres{ adventure, comedy, crime };
	film* grandBudapest = new film("The Grand Budapest Hotel", 2014, "Wes Anderson", grandBudapestProtagonists, grandBudapestGenres, "grandBudapest.png");
	films->push_back(grandBudapest);

	std::vector<std::string> forrestGumpProtagonists{ "Tom Hanks", "Rebecca Williams", "Sally Field" };
	std::vector<genre> forrestGumpGenres{ drama, romance };
	film* forrestGump = new film("Forrest Gump", 1994, "Robert Zemeckis", forrestGumpProtagonists, forrestGumpGenres, "forrestGump.png");
	films->push_back(forrestGump);

	std::vector<std::string> malteseFalconProtagonists{ "Humphrey Bogart", "Mary Astor", "Gladys George" };
	std::vector<genre> malteseFalconGenres{ crime, film_noir, mystery };
	film* malteseFalcon = new film("The Maltese Falcon", 1941, "John Huston", malteseFalconProtagonists, malteseFalconGenres, "malteseFalcon.png");
	films->push_back(malteseFalcon);

	std::vector<std::string> spiritedAwayProtagonists{ "Rumi Hiiragi", "Miyu Irino", "Mari Natsuki" };
	std::vector<genre> spiritedAwayGenres{ adventure, animation, family };
	film* spiritedAway = new film("Spirited Away", 2001, "Hayao Miyazaki", spiritedAwayProtagonists, spiritedAwayGenres, "spiritedAway.png");
	films->push_back(spiritedAway);

	std::vector<std::string> returnKingProtagonists{ "Elijah Wood", "Viggo Mortensen", "Ian McKellen" };
	std::vector<genre> returnKingGenres{ action, adventure, drama };
	film* returnKing = new film("The Lord of the Rings:%% The Return of the King", 2003, "Peter Jackson", returnKingProtagonists, returnKingGenres, "returnKing.png");
	films->push_back(returnKing);

	std::vector<std::string> se7enProtagonists{ "Morgan Freeman", "Brad Pitt", "Kevin Spacey" };
	std::vector<genre> se7enGenres{ crime, drama, mystery };
	film* se7en = new film("Se7en", 1995, "David Fincher", se7enProtagonists, se7enGenres, "se7en.png");
	films->push_back(se7en);

	std::vector<std::string> angryMenProtagonists{ "Henry Fonda", "Lee J. Cobb", "Martin Balsam" };
	std::vector<genre> angryMenGenres{ crime, drama };
	film* angryMen = new film("Twelve Angry Men", 1957, "Sidney Lumet", angryMenProtagonists, angryMenGenres, "angryMen.png");
	films->push_back(angryMen);

	std::vector<std::string> matrixProtagonists{ "Keanu Reeves", "Laurence Fishburne", "Carrie-Anne Moss" };
	std::vector<genre> matrixGenres{ action, sci_fi };
	film* matrix = new film("The Matrix", 1999, "The Wachowskis", matrixProtagonists, matrixGenres, "matrix.png");
	films->push_back(matrix);

	std::vector<std::string> interstellarProtagonists{ "Matthew McConaughey", "Anne Hathaway", "Jessica Chastain" };
	std::vector<genre> interstellarGenres{ adventure, drama, sci_fi };
	film* interstellar = new film("Interstellar", 2014, "Christopher Nolan", interstellarProtagonists, interstellarGenres, "interstellar.png");
	films->push_back(interstellar);

	std::vector<std::string> holyGrailProtagonists{ "Graham Chapman", "John Cleese", "Eric Idle" };
	std::vector<genre> holyGrailGenres{ adventure, comedy, fantasy };
	film* holyGrail = new film("Monty Python and the Holy Grail", 1975, "Terry Gilliam, Terry Jones", holyGrailProtagonists, holyGrailGenres, "holyGrail.png");
	films->push_back(holyGrail);

	return films;

}

