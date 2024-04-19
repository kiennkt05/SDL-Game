#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Variables.h"

using namespace std;

bool F1GP_Load_Leaderboard(){
    ifstream file("Data/Leaderboard.txt");
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        return false;
    }

    int n; 

    file >> n;
    file.ignore();

    // Read leader names
    string name;
    for (int i = 0; i < n; ++i) {
        getline(file, name);
        F1GP_leaderboard.push_back(make_pair(name, 0));
    }

    // Read board scores
    int score;
    for (int i = 0; i < n; ++i) {
        file >> score;
        F1GP_leaderboard[i].second = score;
    }
    
    if ( n == 5 ) F1GP_high_score = F1GP_leaderboard[4].second;

    file.close();

    return true;
}

bool F1GP_Update_Leaderboard(){
    // Write new data to file
    ofstream outFile("Data/Leaderboard.txt");
    if (!outFile.is_open()) {
        cout << "Error opening file for writing." << endl;
        return -1;
    }

    // Write the new number of leaders
    outFile << F1GP_leaderboard.size() << endl;

    // Write leader names
    for (const auto& leader : F1GP_leaderboard) {
        outFile << leader.first << endl;
    }

    // Write board scores
    for (const auto& leader : F1GP_leaderboard) {
        outFile << leader.second << endl;
    }

    outFile.close();
    return true;
}

bool F1GP_Load_History(){
    ifstream file("Data/History.txt");
    if (!file.is_open()) {
        cout << "Error opening file!\n";
        return false;
    }

    int n;  file >> n;
    if ( n == 0 ) 
        return false;
    else {
        file >> F1GP_player_car.pos_x >> F1GP_player_car.pos_y;
        
        for ( auto &opposite_car : F1GP_opposite_car ){
            file >> opposite_car.dx >> opposite_car.dy >> opposite_car.speed
                 >> opposite_car.dx_from_road;

            int img;
            file >> img; opposite_car.image = static_cast<TEXTURE>(img);

            file >> opposite_car.pos_x >> opposite_car.pos_y >> opposite_car.road_id 
                 >> opposite_car.is_empty >> opposite_car.is_add_score >> opposite_car.is_special_box;
        }

        file >> F1GP_last_car_road >> F1GP_player_is_car_fly >> F1GP_player_is_car_transform
             >> F1GP_score >> F1GP_level >> F1GP_pass >> F1GP_fly_count 
             >> F1GP_fly_charger_count >> F1GP_transform_count >> F1GP_run_count;
    }

    file.close();

    return true;    
}

bool F1GP_Update_History(){
    ofstream outfile("Data/History.txt");
    if (!outfile.is_open()) {
        cout << "Error opening file!\n";
        return false;
    }

    if (F1GP_is_crashing) outfile << 0;
    else {
        outfile << 1 << endl;
        outfile << F1GP_player_car.pos_x << " "  << F1GP_player_car.pos_y << endl;
        
        for ( const auto &opposite_car : F1GP_opposite_car ){
            outfile << opposite_car.dx << " " << opposite_car.dy << " " << opposite_car.speed
                    << " " << opposite_car.dx_from_road << " " << static_cast<int>(opposite_car.image)
                    << " " << opposite_car.pos_x << " " << opposite_car.pos_y << " " << opposite_car.road_id 
                    << " " << opposite_car.is_empty << " " << opposite_car.is_add_score 
                    << " " << opposite_car.is_special_box << endl;
        }

        outfile << F1GP_last_car_road << " "  << F1GP_player_is_car_fly << " "  << F1GP_player_is_car_transform
                << " " << F1GP_score << " "  << F1GP_level << " "  << F1GP_pass << " "  << F1GP_fly_count 
                << " " << F1GP_fly_charger_count << " "  << F1GP_transform_count << " "  << F1GP_run_count;
    }
    outfile.close();

    return true;    
}

#endif