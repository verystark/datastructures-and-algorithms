// Datastructures.cc

#include <cstdlib>
#include <cassert>
#include <utility>

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

// return number of all stops
int Datastructures::stop_count()
{
    return Stops_.size();
}

// clear all current data structures
void Datastructures::clear_all()
{
    return Stops_.clear();
}

// go through all stops and return vector consisting of stop IDs
std::vector<StopID> Datastructures::all_stops()
{
    std::vector<StopID> all_stops;
    for (auto stop = Stops_.begin(); stop != Stops_.end(); ++stop) {
        all_stops.push_back(stop->first);
    }
    return all_stops;
}

// add stop with given parameters
bool Datastructures::add_stop(StopID id, const Name& name, Coord xy)
{
    // add new stop, if stop ID not found in stops
    auto result = Stops_.try_emplace(id, Stop_{.stopID_ = id, .name_ = name,  .coord_ = xy});

    // return true if new stop added, return false if stop added
    return result.second;
}

// return stop name with given ID
Name Datastructures::get_stop_name(StopID id)
{
    auto it = Stops_.find(id);

    // if ID found in stops return stop name, else return NO_NAME
    if (it != Stops_.end()) {
        return it->second.name_;
    }
    return NO_NAME;
}

// return stop coordinates with give ID
Coord Datastructures::get_stop_coord(StopID id)
{
    auto it = Stops_.find(id);

    // if ID found in stops return stop name, else return NO_COORD
    if (it != Stops_.end()) {
        return it->second.coord_;
    }
    return NO_COORD;
}

// add struct into vector and sort them alphabetically by name
std::vector<StopID> Datastructures::stops_alphabetically()
{
    // make vector and pre-allocate memory for it
    std::vector<StopID> result;
    result.reserve(Stops_.size());

    // add all IDs to vector
    for (const auto& [id, stop] : Stops_) {
        result.push_back(id);
    }

    // sort vector with IDs based on alphabetical order of names
    std::sort(result.begin(), result.end(), [this](StopID a, StopID b) {
        return Stops_[a].name_ < Stops_[b].name_;
    });

    return result;
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // create empty forward list
    std::forward_list<Stop_> all_structs;

    // add stop struct into forward list
    for (const auto& pair : Stops_) {
        all_structs.push_front(pair.second);
    }

    // sort by name using lambda function
    all_structs.sort([](const Stop_& a, const Stop_& b)
                     {return a.coord_ < b.coord_;});

    std::vector<StopID> result;

    for (const auto& stop : all_structs) {
        result.push_back(stop.stopID_);
    }

    return result;
}

std::vector<StopID> Datastructures::find_stops(Name const& /*name*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::change_stop_name(StopID /*id*/, const Name& /*newname*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::change_stop_coord(StopID /*id*/, Coord /*newcoord*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::add_region(RegionID /*id*/, const Name& /*name*/)
{
    // replace with your implementation
    throw NotImplemented();
}

Name Datastructures::get_region_name(RegionID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<RegionID> Datastructures::all_regions()
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::add_stop_to_region(StopID /*id*/, RegionID /*parentid*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::add_subregion_to_region(RegionID /*id*/, RegionID /*parentid*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<RegionID> Datastructures::stop_regions(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::stops_closest_to(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_stop(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::pair<Coord,Coord> Datastructures::region_bounding_box(RegionID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

RegionID Datastructures::stops_common_region(StopID /*id1*/, StopID /*id2*/)
{
    // replace with your implementation
    throw NotImplemented();
}


bool Datastructures::add_route(RouteID /*id*/, std::vector<StopID> /*stops*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<RouteID> Datastructures::all_routes()
{
    // replace with your implementation
    throw NotImplemented();
}

bool Datastructures::remove_route(RouteID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::pair<RouteID, StopID>> Datastructures::routes_from(StopID /*stopid*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::route_stops(RouteID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

void Datastructures::clear_routes()
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_any(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();

}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_least_stops(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_with_cycle(StopID /*fromstop*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<std::tuple<StopID, RouteID, Distance>> Datastructures::journey_shortest_distance(StopID /*fromstop*/, StopID /*tostop*/)
{
    // replace with your implementation
    throw NotImplemented();
}


