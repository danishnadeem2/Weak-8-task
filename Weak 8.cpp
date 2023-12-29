#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const int HOURLY_RATE = 20;
const int HALF_HOUR_RATE = 12;
const int OPENING_TIME = 10;
const int CLOSING_TIME = 17;

struct Boat 
{
    bool available;
    int total_money;
    float total_hours;
    tm return_time;
};

vector<Boat> boats(10);

void calculate_money_for_one_boat(int boat_number, float hours) 
{
    Boat& boat = boats[boat_number - 1];

    // Check if boat is available
    if (!boat.available) 
    {
        cout << "Boat " << boat_number << " is not available. Next available time is " << asctime(&boat.return_time);
        return;
    }

    // Validate opening and closing time
    time_t t = time(0);
    tm* now = localtime(&t);
    int current_time = now->tm_hour;

    if (current_time < OPENING_TIME || current_time >= CLOSING_TIME || (current_time == CLOSING_TIME && now->tm_min > 0)) 
    {
        cout << "Boat can only be hired between 10:00 and 17:00." << endl;
        return;
    }

    // Calculate cost and update boat information
    int cost;
    if (hours == 0.5) 
    {
        cost = HALF_HOUR_RATE;
    }
    else if (hours == 1) 
    {
        cost = HOURLY_RATE;
    }
    else 
    {
        cout << "Invalid duration. Please choose 0.5 or 1 hour." << endl;
        return;
    }

    int hours_int = static_cast<int>(hours);
    int minutes_int = static_cast<int>((hours - hours_int) * 60);

    boat.return_time.tm_hour += hours_int;
    boat.return_time.tm_min += minutes_int;

    // Adjust if minutes exceed 60
    boat.return_time.tm_hour += boat.return_time.tm_min / 60;
    boat.return_time.tm_min %= 60;

    boat.available = false;
    boat.total_money += cost;
    boat.total_hours += hours;

    cout << "Boat " << boat_number << " hired for " << hours << " hours. Total cost: $" << cost << ". Return by " << asctime(&boat.return_time);
}

void find_next_available_boat() 
{
    time_t t = time(0);
    tm* now = localtime(&t);
    int current_time = now->tm_hour;

    for (int boat_number = 1; boat_number <= 10; ++boat_number) 
    {
        Boat& boat = boats[boat_number - 1];
        if (boat.available) 
        {
            cout << "Boat " << boat_number << " is available for hire." << endl;
        }
        else 
        {
            cout << "Boat " << boat_number << " is not available. Next available time is " << asctime(&boat.return_time);
        }
    }
}

void calculate_money_for_all_boats() 
{
    int total_money = 0;
    float total_hours = 0;
    int unused_boats = 0;

    Boat max_used_boat = boats[0];

    for (const Boat& boat : boats) 
    {
        total_money += boat.total_money;
        total_hours += boat.total_hours;
        if (boat.total_hours == 0)
        {
            unused_boats++;
        }

        if (boat.total_hours > max_used_boat.total_hours) 
        {
            max_used_boat = boat;
        }
    }

    cout << "Total money taken for all boats: $" << total_money << endl;
    cout << "Total hours boats were hired: " << total_hours << " hours" << endl;
    cout << "Number of boats not used: " << unused_boats << endl;
    cout << "Boat " << &max_used_boat - &boats[0] + 1 << " was used the most with " << max_used_boat.total_hours << " hours." << endl;
}

int main() 
{
    // Testing Task 1
    calculate_money_for_one_boat(1, 1.5);  // Testing with 1.5 hours

    // Testing Task 2
    find_next_available_boat();

    // Testing Task 3
    calculate_money_for_all_boats();

    return 0;
}