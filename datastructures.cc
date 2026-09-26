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

bool Datastructures::add_stop(StopID /*id*/, const Name& /*name*/, Coord /*xy*/)
{
    // replace with your implementation
    throw NotImplemented();

}

Name Datastructures::get_stop_name(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

Coord Datastructures::get_stop_coord(StopID /*id*/)
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::stops_alphabetically()
{
    // replace with your implementation
    throw NotImplemented();
}

std::vector<StopID> Datastructures::stops_coord_order()
{
    // replace with your implementation
    throw NotImplemented();
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


