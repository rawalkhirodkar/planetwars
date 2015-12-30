#include "PlanetWars.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct sort_value
{
    inline bool operator() (const Planet& p1, const Planet& p2)
    {
        return (p1.value < p2.value);
    }
}; // used to sort the planets using threshold value in ascending order

void myprint1(std::string s,double k){
  std:: ofstream print;
  print.open("print.txt", std::ofstream:: app);
  print << s<<":"<<k << std::endl;
}

void StringUtil::Tokenize(const std::string& s,
                          const std::string& delimiters,
                          std::vector<std::string>& tokens) {
  std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
  std::string::size_type pos = s.find_first_of(delimiters, lastPos);
  while (std::string::npos != pos || std::string::npos != lastPos) {
    tokens.push_back(s.substr(lastPos, pos - lastPos));
    lastPos = s.find_first_not_of(delimiters, pos);
    pos = s.find_first_of(delimiters, lastPos);
  }
}

std::vector<std::string> StringUtil::Tokenize(const std::string& s,
                                              const std::string& delimiters) {
  std::vector<std::string> tokens;
  Tokenize(s, delimiters, tokens);
  return tokens;
}

Fleet::Fleet(int owner,
             int num_ships,
             int source_planet,
             int destination_planet,
             int total_trip_length,
             int turns_remaining) {
  owner_ = owner;
  num_ships_ = num_ships;
  source_planet_ = source_planet;
  destination_planet_ = destination_planet;
  total_trip_length_ = total_trip_length;
  turns_remaining_ = turns_remaining;
}

int Fleet::Owner() const {
  return owner_;
}

int Fleet::NumShips() const {
  return num_ships_;
}

int Fleet::SourcePlanet() const {
  return source_planet_;
}

int Fleet::DestinationPlanet() const {
  return destination_planet_;
}

int Fleet::TotalTripLength() const {
  return total_trip_length_;
}

int Fleet::TurnsRemaining() const {
  return turns_remaining_;
}

Planet::Planet(int planet_id,
               int owner,
               int num_ships,
               int growth_rate,
               double x,
               double y) {
  planet_id_ = planet_id;
  owner_ = owner;
  num_ships_ = num_ships;
  growth_rate_ = growth_rate;
  x_ = x;
  y_ = y;
}

int Planet::PlanetID() const {
  return planet_id_;
}

int Planet::Owner() const {
  return owner_;
}

int Planet::NumShips() const {
  return num_ships_;
}

int Planet::GrowthRate() const {
  return growth_rate_;
}

double Planet::X() const {
  return x_;
}

double Planet::Y() const {
  return y_;
}

void Planet::Owner(int new_owner) {
  owner_ = new_owner;
}

void Planet::NumShips(int new_num_ships) {
  num_ships_ = new_num_ships;
}

void Planet::AddShips(int amount) {
  num_ships_ += amount;
}

void Planet::RemoveShips(int amount) {
  num_ships_ -= amount;
}

PlanetWars::PlanetWars(const std::string& gameState) {
  ParseGameState(gameState);
}

int PlanetWars::NumPlanets() const {
  return planets_.size();
}

const Planet& PlanetWars::GetPlanet(int planet_id) const {
  return planets_[planet_id];
}

int PlanetWars::NumFleets() const {
  return fleets_.size();
}

const Fleet& PlanetWars::GetFleet(int fleet_id) const {
  return fleets_[fleet_id];
}

std::vector<Planet> PlanetWars::Planets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    r.push_back(p);
  }
  return r;
}

std::vector<Planet> PlanetWars::MyPlanets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    if (p.Owner() == 1) {
      r.push_back(p);
    }
  }
  return r;
}

std::vector<Planet> PlanetWars::NeutralPlanets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    if (p.Owner() == 0) {
      r.push_back(p);
    }
  }
  return r;
}

std::vector<Planet> PlanetWars::EnemyPlanets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    if (p.Owner() > 1) {
      r.push_back(p);
    }
  }
  return r;
}

std::vector<Planet> PlanetWars::NotMyPlanets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    if (p.Owner() != 1) {
      r.push_back(p);
    }
  }
  return r;
}

std::vector<Fleet> PlanetWars::Fleets() const {
  std::vector<Fleet> r;
  for (int i = 0; i < fleets_.size(); ++i) {
    const Fleet& f = fleets_[i];
    r.push_back(f);
  }
  return r;
}

std::vector<Fleet> PlanetWars::MyFleets() const {
  std::vector<Fleet> r;
  for (int i = 0; i < fleets_.size(); ++i) {
    const Fleet& f = fleets_[i];
    if (f.Owner() == 1) {
      r.push_back(f);
    }
  }
  return r;
}

std::vector<Fleet> PlanetWars::EnemyFleets() const {
  std::vector<Fleet> r;
  for (int i = 0; i < fleets_.size(); ++i) {
    const Fleet& f = fleets_[i];
    if (f.Owner() > 1) {
      r.push_back(f);
    }
  }
  return r;
}

std::string PlanetWars::ToString() const {
  std::stringstream s;
  for (unsigned int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    s << "P " << p.X() << " " << p.Y() << " " << p.Owner()
      << " " << p.NumShips() << " " << p.GrowthRate() << std::endl;
  }
  for (unsigned int i = 0; i < fleets_.size(); ++i) {
    const Fleet& f = fleets_[i];
    s << "F " << f.Owner() << " " << f.NumShips() << " "
      << f.SourcePlanet() << " " << f.DestinationPlanet() << " "
      << f.TotalTripLength() << " " << f.TurnsRemaining() << std::endl;
  }
  return s.str();
}

int PlanetWars::Distance(int source_planet, int destination_planet) const {
  const Planet& source = planets_[source_planet];
  const Planet& destination = planets_[destination_planet];
  double dx = source.X() - destination.X();
  double dy = source.Y() - destination.Y();
  return (int)ceil(sqrt(dx * dx + dy * dy));
}

void PlanetWars::IssueOrder(int source_planet,
                            int destination_planet,
                            int num_ships) const {
  std::cout << source_planet << " "
            << destination_planet << " "
            << num_ships << std::endl;
  std::cout.flush();
}

bool PlanetWars::IsAlive(int player_id) const {
  for (unsigned int i = 0; i < planets_.size(); ++i) {
    if (planets_[i].Owner() == player_id) {
      return true;
    }
  }
  for (unsigned int i = 0; i < fleets_.size(); ++i) {
    if (fleets_[i].Owner() == player_id) {
      return true;
    }
  }
  return false;
}

int PlanetWars::NumShips(int player_id) const {
  int num_ships = 0;
  for (unsigned int i = 0; i < planets_.size(); ++i) {
    if (planets_[i].Owner() == player_id) {
      num_ships += planets_[i].NumShips();
    }
  }
  for (unsigned int i = 0; i < fleets_.size(); ++i) {
    if (fleets_[i].Owner() == player_id) {
      num_ships += fleets_[i].NumShips();
    }
  }
  return num_ships;
}

int PlanetWars::ParseGameState(const std::string& s) {
  planets_.clear();
  fleets_.clear();
  std::vector<std::string> lines = StringUtil::Tokenize(s, "\n");
  int planet_id = 0;
  for (unsigned int i = 0; i < lines.size(); ++i) {
    std::string& line = lines[i];
    size_t comment_begin = line.find_first_of('#');
    if (comment_begin != std::string::npos) {
      line = line.substr(0, comment_begin);
    }
    std::vector<std::string> tokens = StringUtil::Tokenize(line);
    if (tokens.size() == 0) {
      continue;
    }
    if (tokens[0] == "P") {
      if (tokens.size() != 6) {
        return 0;
      }
      Planet p(planet_id++,              // The ID of this planet
	       atoi(tokens[3].c_str()),  // Owner
               atoi(tokens[4].c_str()),  // Num ships
               atoi(tokens[5].c_str()),  // Growth rate
               atof(tokens[1].c_str()),  // X
               atof(tokens[2].c_str())); // Y
      planets_.push_back(p);
    } else if (tokens[0] == "F") {
      if (tokens.size() != 7) {
        return 0;
      }
      Fleet f(atoi(tokens[1].c_str()),  // Owner
              atoi(tokens[2].c_str()),  // Num ships
              atoi(tokens[3].c_str()),  // Source
              atoi(tokens[4].c_str()),  // Destination
              atoi(tokens[5].c_str()),  // Total trip length
              atoi(tokens[6].c_str())); // Turns remaining
      fleets_.push_back(f);
    } else {
      return 0;
    }
  }
  return 1;
}

void PlanetWars::FinishTurn() const {
  std::cout << "go" << std::endl;
  std::cout.flush();
}


//--------------------------------------------------------------------------------
Command::Command(int s, int d, int send){
	source_planet = s;
	destination_planet = d;
	ships_send = send;
}

// //--------------------------------------------------------------------------------
// // given a source planet, finds optimal target (enemy/neutral)
// int PlanetWars::optimalTarget(int source_id){
//   	double final_score = -999999;
// 	int target_index = -1;
//   	double scale = -1;
//   	for(int i = 0 ; i < planets_.size(); i++){
//     	if(planets_[i].Owner() != 1){
//       		if(scale < planets_[i].NumShips()){
//         		scale = planets_[i].NumShips();
//       		}
//     	}
//   	}
//   	int weight;
// 		for(int i = 0 ; i < planets_.size(); i++){
// 			if(planets_[i].Owner() != 1){
// 				double dist = Distance(source_id,planets_[i].PlanetID());
//       			double num = 1 + planets_[i].GrowthRate();
//       			double den = dist * (1+planets_[i].NumShips());
// 				double score = (double)((num*scale)/den);
// 				if(score > final_score){
// 					target_index = i;
// 					final_score = score;
// 				}
// 			}
// 		}
// 	return target_index;
// }

//--------------------------------------------------------------------------------
void PlanetWars::UpdatePlanet(int planet_index, int owner, int ships_left){
	planets_[planet_index].Owner(owner);
	planets_[planet_index].NumShips(ships_left);
	return;
}

//--------------------------------------------------------------------------------
int PlanetWars::Threshold(int planet_id){
  int friend_radius = 4;
  int enemy_radius = 6;
  int defense = 0;
  int attack = 0;
  for(int i = 0 ; i < planets_.size(); i++){
    if(planets_[i].Owner() == 1){
      int dist = Distance(planet_id, planets_[i].PlanetID());
      if(dist <= friend_radius){
        defense += planets_[i].NumShips();
      }
    }
    else if(planets_[i].Owner() == 2){
      int dist = Distance(planet_id, planets_[i].PlanetID());
      if(dist <= enemy_radius){
        attack += planets_[i].NumShips();
      }
    }
  }
  int threshold = 3*planets_[planet_id].GrowthRate();
  if(threshold < attack-defense ){
    threshold = attack-defense;
  }
  return threshold;
}

//--------------------------------------------------------------------------------
int PlanetWars::Capturability(int planet_id){
  int friend_radius = 4;
  int enemy_radius = 6;
  int defense = 0;
  int attack = planets_[planet_id].NumShips();
  for(int i = 0 ; i < planets_.size(); i++){
    if(planets_[i].Owner() == 1){
      int dist = Distance(planet_id, planets_[i].PlanetID());
      if(dist <= friend_radius){
        defense += planets_[i].NumShips();
      }
    }
    else if(planets_[i].Owner() == 2){
      int dist = Distance(planet_id, planets_[i].PlanetID());
      if(dist <= enemy_radius){
        attack += planets_[i].NumShips();
      }
    }
  }
  return attack-defense;
}

//--------------------------------------------------------------------------------
PlanetWars PlanetWars::fastForwardFleets(){
  PlanetWars new_state = *this;
  for(int i = 0 ; i < fleets_.size(); i++){
    int destination_planet = fleets_[i].DestinationPlanet();
    int fleet_size = fleets_[i].NumShips();
    int defending_ships = planets_[destination_planet].NumShips();
    int defending_player = planets_[destination_planet].Owner();
    int final_owner = defending_player;
    if(fleet_size > defending_ships){
      final_owner = fleets_[i].Owner();
    }
    new_state.UpdatePlanet(destination_planet,final_owner,std::abs(fleet_size-defending_ships));
  }
  return new_state;
}

//--------------------------------------------------------------------------------
void PlanetWars::findPossibleStates(std::vector<PlanetWars>& possibleStates){
	// the new states created will never have fleets in mid-air right now
	std::vector<Planet> my_planets = MyPlanets();
	std::vector<Planet> not_my_planets = NotMyPlanets();
	std::vector<Planet> enemy_planets;
	std::vector<Planet> neutral_planets;
	std::vector<Planet> cand_planets;
	for(int i=0; i< my_planets.size(); i++){
		int planet_id = my_planets[i].PlanetID();
		int excess_ships = my_planets[i].NumShips()-Threshold(planet_id);
		if(excess_ships > 0){ cand_planets.push_back(my_planets[i]); }
	}// can be improved!

	// four branches, mix, defense, enemy attack, neutral attack
	for(int i = 0 ; i < not_my_planets.size(); i++){
		not_my_planets[i].value = Capturability(not_my_planets[i].PlanetID());
	}
	std::sort(not_my_planets.begin(), not_my_planets.end(), sort_value());

	for(int i = 0 ; i < not_my_planets.size(); i++){
		if(not_my_planets[i].Owner() == 2){
	  		enemy_planets.push_back(not_my_planets[i]);
		}
		if(not_my_planets[i].Owner() == 0){
	  		neutral_planets.push_back(not_my_planets[i]);
		}
	}// creating rest vector for other branches

	//-----------------------branch 1 Mixed Strategy------------------------------------------
	PlanetWars new_state = *this;
	for(int i=0;i<cand_planets.size();i++){
		int planet_id = cand_planets[i].PlanetID();
		int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
		
		for(int j=0;j<not_my_planets.size();j++){
			if(new_state.planets_[not_my_planets[j].PlanetID()].Owner() != 1){
	  			if(excess_ships > 0){
	    			int ships_sent = 0;
	    			// if( excess_ships < (not_my_planets[j].NumShips()+1) ){
	    			// 	ships_sent = excess_ships;
	    			// 	new_state.UpdatePlanet(not_my_planets[j].PlanetID(),not_my_planets[j].Owner(),not_my_planets[j].NumShips()-ships_sent);
	    			// 	excess_ships = 0;
	    			// 	new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			// }
	    			if( excess_ships >= (not_my_planets[j].NumShips()+1) ){
	    				ships_sent = not_my_planets[j].NumShips()+1;
	    				new_state.UpdatePlanet(not_my_planets[j].PlanetID(),1,1);
	    				excess_ships = excess_ships - ships_sent;
	    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			}
	    		}
	    		else if(excess_ships <= 0) break;
	    	}
		}

		if(excess_ships > 0){
			// redistribute
		}
	}

	possibleStates.push_back(new_state);

	//-----------------------branch 2 Redistribute only ------------------------------------------
	new_state = *this;
	for(int i=0;i<cand_planets.size();i++){
		int planet_id = cand_planets[i].PlanetID();
		int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	

		if(excess_ships > 0){
			// redistribute
		}
	}

	possibleStates.push_back(new_state);

	//-----------------------branch 3 Enemy Attack  Redistribute only ----------------------------
	new_state = *this;
	for(int i=0;i<cand_planets.size();i++){
		int planet_id = cand_planets[i].PlanetID();
		int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
		
		for(int j=0;j<enemy_planets.size();j++){
			if(new_state.planets_[enemy_planets[j].PlanetID()].Owner()!= 1){
	  			if(excess_ships > 0){
	    			int ships_sent = 0;
	    			// if( excess_ships < (enemy_planets[j].NumShips()+1) ){
	    			// 	ships_sent = excess_ships;
	    			// 	new_state.UpdatePlanet(enemy_planets[j].PlanetID(),enemy_planets[j].Owner(),enemy_planets[j].NumShips()-ships_sent);
	    			// 	excess_ships = 0;
	    			// 	new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			// }
	    			if( excess_ships >= (enemy_planets[j].NumShips()+1) ){
	    				ships_sent = enemy_planets[j].NumShips()+1;
	    				new_state.UpdatePlanet(enemy_planets[j].PlanetID(),1,1);
	    				excess_ships = excess_ships - ships_sent;
	    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			}
	    		}

	    	else if(excess_ships <= 0) break;
	    	}
		}

		if(excess_ships > 0){
			// redistribute
		}
	}

	possibleStates.push_back(new_state);

	//-----------------------branch 4 Neutral Attack  Redistribute only ----------------------------
	new_state = *this;
	for(int i=0;i<cand_planets.size();i++){
		int planet_id = cand_planets[i].PlanetID();
		int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
		
		for(int j=0;j<neutral_planets.size();j++){
			if(new_state.planets_[neutral_planets[j].PlanetID()].Owner() != 1){
	  			if(excess_ships > 0){
	    			int ships_sent = 0;
	    			// if( excess_ships < (neutral_planets[j].NumShips()+1) ){
	    			// 	ships_sent = excess_ships;
	    			// 	new_state.UpdatePlanet(neutral_planets[j].PlanetID(),neutral_planets[j].Owner(),neutral_planets[j].NumShips()-ships_sent);
	    			// 	excess_ships = 0;
	    			// 	new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			// }
	    			if( excess_ships >= (neutral_planets[j].NumShips()+1) ){
	    				ships_sent = neutral_planets[j].NumShips()+1;
	    				new_state.UpdatePlanet(neutral_planets[j].PlanetID(),1,1);
	    				excess_ships = excess_ships - ships_sent;
	    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
	    			}
	    		}

	    	else if(excess_ships <= 0) break;
	    	}
		}

		if(excess_ships > 0){
			// redistribute
		}
	}

	possibleStates.push_back(new_state);

}

//--------------------------------------------------------------------------------
void PlanetWars::findPossibleOp(std::vector<Command>& op, int& returnstate){
    // the new states created will never have fleets in mid-air right now
	std::vector<Planet> my_planets = MyPlanets();
	std::vector<Planet> not_my_planets = NotMyPlanets();
	std::vector<Planet> enemy_planets;
	std::vector<Planet> neutral_planets;
	std::vector<Planet> cand_planets;
	for(int i=0; i< my_planets.size(); i++){
		int planet_id = my_planets[i].PlanetID();
		int excess_ships = my_planets[i].NumShips()-Threshold(planet_id);
		if(excess_ships > 0){ cand_planets.push_back(my_planets[i]); }
	}

	// four branches, mix, defense, enemy attack, neutral attack
	for(int i = 0 ; i < not_my_planets.size(); i++){
		not_my_planets[i].value = Capturability(not_my_planets[i].PlanetID());
	}
	std::sort(not_my_planets.begin(), not_my_planets.end(), sort_value());

	for(int i = 0 ; i < not_my_planets.size(); i++){
		if(not_my_planets[i].Owner() == 2){
	  		enemy_planets.push_back(not_my_planets[i]);
		}
		if(not_my_planets[i].Owner() == 0){
	  		neutral_planets.push_back(not_my_planets[i]);
		}
	}// creating rest vector for other branches

	//-----------------------branch 1 Mixed Strategy------------------------------------------
	if(returnstate == 0){
		PlanetWars new_state = *this;
		for(int i=0;i<cand_planets.size();i++){
			int planet_id = cand_planets[i].PlanetID();
			int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
			
			for(int j=0;j<not_my_planets.size();j++){
				if(new_state.planets_[not_my_planets[j].PlanetID()].Owner() != 1){
		  			if(excess_ships > 0){
		    			int ships_sent = 0;
		    			if( excess_ships >= (not_my_planets[j].NumShips()+1) ){
		    				ships_sent = not_my_planets[j].NumShips()+1;
		    				new_state.UpdatePlanet(not_my_planets[j].PlanetID(),1,1);
		    				excess_ships = excess_ships - ships_sent;
		    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
		    				op.push_back(Command(cand_planets[i].PlanetID(),not_my_planets[j].PlanetID(),ships_sent));
		    			}
		    		}
		    		else if(excess_ships <= 0) break;
		    	}
			}

			if(excess_ships > 0){
				// redistribute
			}
		}
	}

	//-----------------------branch 2 Redistribute only ------------------------------------------
	else if(returnstate == 1){
		PlanetWars new_state = *this;
		for(int i=0;i<cand_planets.size();i++){
			int planet_id = cand_planets[i].PlanetID();
			int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	

			if(excess_ships > 0){
				// redistribute
			}
		}
	}

	//-----------------------branch 3 Enemy Attack  Redistribute only ----------------------------
	else if(returnstate == 2){
		PlanetWars new_state = *this;
		for(int i=0;i<cand_planets.size();i++){
			int planet_id = cand_planets[i].PlanetID();
			int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
			
			for(int j=0;j<enemy_planets.size();j++){
				if(new_state.planets_[enemy_planets[j].PlanetID()].Owner() != 1){
		  			if(excess_ships > 0){
		    			int ships_sent = 0;
		    			// if( excess_ships < (enemy_planets[j].NumShips()+1) ){
		    			// 	ships_sent = excess_ships;
		    			// 	new_state.UpdatePlanet(enemy_planets[j].PlanetID(),enemy_planets[j].Owner(),enemy_planets[j].NumShips()-ships_sent);
		    			// 	excess_ships = 0;
		    			// 	new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
		    			// 	op.push_back(Command(cand_planets[i].PlanetID(),enemy_planets[j].PlanetID(),ships_sent));
		    			// }
		    			if( excess_ships >= (enemy_planets[j].NumShips()+1) ){
		    				ships_sent = enemy_planets[j].NumShips()+1;
		    				new_state.UpdatePlanet(enemy_planets[j].PlanetID(),1,1);
		    				excess_ships = excess_ships - ships_sent;
		    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
		    				op.push_back(Command(cand_planets[i].PlanetID(),enemy_planets[j].PlanetID(),ships_sent));
		    			}
		    		}

		    	else if(excess_ships <= 0) break;
		    	}
			}

			if(excess_ships > 0){
				// redistribute
			}
		}
	}

	//-----------------------branch 4 Neutral Attack  Redistribute only ----------------------------
	else if(returnstate == 3){
		PlanetWars new_state = *this;
		for(int i=0;i<cand_planets.size();i++){
			int planet_id = cand_planets[i].PlanetID();
			int excess_ships = cand_planets[i].NumShips()-Threshold(planet_id);	
			
			for(int j=0;j<neutral_planets.size();j++){
				if(new_state.planets_[neutral_planets[j].PlanetID()].Owner() != 1){
		  			if(excess_ships > 0){
		    			int ships_sent = 0;
		    			// if( excess_ships < (neutral_planets[j].NumShips()+1) ){
		    			// 	ships_sent = excess_ships;
		    			// 	new_state.UpdatePlanet(neutral_planets[j].PlanetID(),neutral_planets[j].Owner(),neutral_planets[j].NumShips()-ships_sent);
		    			// 	excess_ships = 0;
		    			// 	new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
		    			// 	op.push_back(Command(cand_planets[i].PlanetID(),neutral_planets[j].PlanetID(),ships_sent));
		    			// }
		    			if( excess_ships >= (neutral_planets[j].NumShips()+1) ){
		    				ships_sent = neutral_planets[j].NumShips()+1;
		    				new_state.UpdatePlanet(neutral_planets[j].PlanetID(),1,1);
		    				excess_ships = excess_ships - ships_sent;
		    				new_state.UpdatePlanet(cand_planets[i].PlanetID(),1,cand_planets[i].NumShips()-ships_sent);
		    				op.push_back(Command(cand_planets[i].PlanetID(),neutral_planets[j].PlanetID(),ships_sent));
		    			}
		    		}

		    	else if(excess_ships <= 0) break;
		    	}
			}

			if(excess_ships > 0){
				// redistribute
			}
		}
	}
}

//--------------------------------------------------------------------------------
int PlanetWars::evaluation_function(){
  double score = 0; int weight = 2;
  int friend_score = 0 ;
  int enemy_score = 0;
  for(int i = 0 ; i < planets_.size(); i++){
    if(planets_[i].Owner() == 1){
      weight = 2;
      //friend_score += Closeness(planets_[i].PlanetID());
    }
    else if(planets_[i].Owner() == 2){
      weight = -2;
      //enemy_score += Closeness(planets_[i].PlanetID());
    }
    else{
      weight = 1;
    }
    score += weight*planets_[i].GrowthRate()*(1+planets_[i].NumShips());
  }
  
  //myprint1("prev",score);
  //score = score *((double)(1+friend_score)/(1+enemy_score));
 // myprint1("final",score);
  return score;
}