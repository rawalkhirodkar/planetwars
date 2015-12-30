#include <iostream>
#include "PlanetWars.h"
#include <fstream>
#include <limits>
#include <string>
#include <ctime>

#define inf std::numeric_limits<int>::max()
#define ninf std::numeric_limits<int>::min()

void myprint(std::string s,int k){
	std:: ofstream print;
	print.open("print.txt", std::ofstream:: app);
	print << s<<":"<<k << std::endl;
}

void myprintx(std::string s,double k){
  std:: ofstream print;
  print.open("print.txt", std::ofstream:: app);
  print << s<<":"<<k << std::endl;
}

void myprint_issueorder(int src, int dest, int ships){
	myprint("source_planet",src);
	myprint("destination_planet",dest);
	myprint("ships_send",ships);
	myprint("---------------------------------------------------------------------------",1);
}

void debug(PlanetWars root){
	std::vector<PlanetWars> v;
	root.findPossibleStates(v);

	std:: ofstream print;
	print.open("debug.txt", std::ofstream:: app);

	print << "ROOT EvaluationScore:"<<root.evaluation_function()<< std::endl;
	std::vector<Planet> my_planets = root.MyPlanets();
	std::vector<Planet> neutral_planets = root.NeutralPlanets();
	std::vector<Planet> enemy_planets = root.EnemyPlanets();
	print << "my_planets:"<< std::endl;
	for(int j = 0 ; j < my_planets.size(); j++){
		print<<"PlanetID:"<<my_planets[j].PlanetID()<<" Ships:"<<my_planets[j].NumShips()<<" Owner:"<<my_planets[j].Owner() <<" Growth:"<< my_planets[j].GrowthRate() << std::endl;
	}

	print << "neutral_planets:"<< std::endl;
	for(int j = 0 ; j < neutral_planets.size(); j++){
		print<<"PlanetID:"<<neutral_planets[j].PlanetID()<<" Ships:"<<neutral_planets[j].NumShips()<<" Owner:"<<neutral_planets[j].Owner() <<" Growth:"<< neutral_planets[j].GrowthRate() << std::endl;
	}

	print << "enemy_planets:"<< std::endl;
	for(int j = 0 ; j < enemy_planets.size(); j++){
		print<<"PlanetID:"<<enemy_planets[j].PlanetID()<<" Ships:"<<enemy_planets[j].NumShips()<<" Owner:"<<enemy_planets[j].Owner() <<" Growth:"<< enemy_planets[j].GrowthRate() << std::endl;
	}

	for(int i = 0 ; i < v.size(); i++){
		std::vector<Planet> my_planets = v[i].MyPlanets();
		std::vector<Planet> neutral_planets = v[i].NeutralPlanets();
		std::vector<Planet> enemy_planets = v[i].EnemyPlanets();
		print << "State:" << i << " EvaluationScore:"<< v[i].evaluation_function()<< std::endl;
		print << "my_planets:"<< std::endl;
		for(int j = 0 ; j <  my_planets.size(); j++){
			print<<"PlanetID:"<< my_planets[j].PlanetID()<<" Ships:"<< my_planets[j].NumShips()<<" Owner:"<< my_planets[j].Owner() <<" Growth:"<<  my_planets[j].GrowthRate() << std::endl;
		}

		print << "neutral_planets:"<< std::endl;
		for(int j = 0 ; j <  neutral_planets.size(); j++){
			print<<"PlanetID:"<< neutral_planets[j].PlanetID()<<" Ships:"<< neutral_planets[j].NumShips()<<" Owner:"<< neutral_planets[j].Owner() <<" Growth:"<<  neutral_planets[j].GrowthRate() << std::endl;
		}

		print << "enemy_planets:"<< std::endl;
		for(int j = 0 ; j <  enemy_planets.size(); j++){
			print<<"PlanetID:"<< enemy_planets[j].PlanetID()<<" Ships:"<< enemy_planets[j].NumShips()<<" Owner:"<< enemy_planets[j].Owner() <<" Growth:"<<  enemy_planets[j].GrowthRate() << std::endl;
		}
	}
	print <<"----------------------------------------------------" <<std::endl<< std::endl;
}

int alphabeta(int player, PlanetWars& x, int depth, int alpha, int beta, int& returnstate, int maxdepth){
	if(depth == 0){ 
		//myprint("evaluation",x.evaluation_function());
		return x.evaluation_function(); 
	}
	std::vector<PlanetWars> possible;
	x.findPossibleStates(possible);
	//myprint("size",possible.size());
	if(possible.size()==0){ return x.evaluation_function(); }
	int nplayer; 
	if(player == 1){
		nplayer = 2; 
		for(int i=0; i<possible.size(); i++){
			if(depth != maxdepth){
				if(alpha <= beta){
					int temp = alphabeta(nplayer, possible[i], depth-1, alpha, beta, returnstate, maxdepth);
					if(temp > alpha){ alpha = temp; }
				}
				// else break;
			}
			if(depth == maxdepth){
				if(alpha <= beta){
					int temp = alphabeta(nplayer, possible[i], depth-1, alpha, beta, returnstate, maxdepth);
					if(temp > alpha){ alpha = temp; returnstate = i; }
					// print("alphabeta",0);
				}
				// else break;
			}
		}
		return alpha;
	}
	else{
		nplayer = 1;
		for(int i=0; i<possible.size(); i++){
			if(alpha <= beta){
				int temp = alphabeta(nplayer, possible[i], depth-1, alpha, beta, returnstate, maxdepth);
				if(temp < beta){ beta = temp; }
			}
			// else break;
		}
		return beta;
	}
}

void DoTurn(PlanetWars& pw) {
	//debug(pw);
	PlanetWars root = pw.fastForwardFleets();
	int alpha = ninf;
	int beta = inf;
	int returnstate = -1;
	int depth = 3;
	double time_used = 0;
	int k = alphabeta(1,root,depth,alpha,beta,returnstate,depth); 
	std::vector<Command> op;
	root.findPossibleOp(op, returnstate);
	if(returnstate<0 || op.size() == 0) {return;}
	//myprint("return",returnstate);
	for(int i =0; i< op.size(); i++){
		Planet source_planet = pw.GetPlanet(op[i].source_planet);
		if((source_planet.NumShips() > op[i].ships_send) && source_planet.Owner() == 1 ){
			//myprint_issueorder(op[returnstate].moves[i].source_planet,op[returnstate].moves[i].destination_planet,op[returnstate].moves[i].ships_send);
			pw.IssueOrder(op[i].source_planet,op[i].destination_planet,op[i].ships_send);
			//pw.UpdatePlanet(op[returnstate].moves[i].source_planet,op[returnstate].moves[i].destination_planet,op[returnstate].moves[i].ships_send);
		}
	}
}


// This is just the main game loop that takes care of communicating with the
// game engine for you. You don't have to understand or change the code below.
int main(int argc, char *argv[]) {
  std::string current_line;
  std::string map_data;
  while (true) {
    int c = std::cin.get();
    current_line += (char)c;
    if (c == '\n') {
      if (current_line.length() >= 2 && current_line.substr(0, 2) == "go") {
        PlanetWars pw(map_data);
        map_data = "";
        DoTurn(pw);
	pw.FinishTurn();
      } else {
        map_data += current_line;
      }
      current_line = "";
    }
  }
  return 0;
}
