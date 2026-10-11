// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <source_location>

// Omat includet
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstddef>
#include <memory>
#include <forward_list>
#include <cmath>
#include <queue>
#include <algorithm>

// Types for IDs
using StopID = long int;
using RegionID = std::string;
using RouteID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
RouteID const NO_ROUTE = "!!NO_ROUTE!!";
StopID const NO_STOP = -1;
RegionID const NO_REGION = "!!NO_REGION!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;


// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    explicit NotImplemented(std::string const msg = "",
                            const std::source_location location = std::source_location::current())
        : msg_{}
    {
        std::string funcname = location.function_name();
        if (auto namestart = funcname.find_last_of(':'); namestart != std::string::npos)
        { funcname.erase(0, namestart+1); }
        if (auto nameend = funcname.find_first_of('('); nameend != std::string::npos)
        { funcname.erase(nameend, std::string::npos); }
        msg_ = (!msg.empty() ? msg+" in " : "")+funcname+"()";
    }
    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// ---------------------------------------------------------------------------------------
// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: Theta(1)
    // Short rationale for estimate: std::unordered_map::size() is a constant-time operation
    int stop_count();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: std::unordered_map::clear() destroys all elements linearly
    void clear_all();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Iterates through all elements in Stops_ once and copies IDs to a vector pre-allocated with reserve()
    std::vector<StopID> all_stops();

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::try_emplace performs hash lookup and insertion in average constant time
    bool add_stop(StopID id, Name const& name, Coord xy);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::find provides average constant-time key lookup
    Name get_stop_name(StopID);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::find provides average constant-time key lookup
    Coord get_stop_coord(StopID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: Theta(n log(n))
    // Short rationale for estimate: Copying IDs takes Theta(n) and std::sort takes Theta(n log n) time. Lookup inside lambda is average Theta(1)
    std::vector<StopID> stops_alphabetically();

    // Estimate of performance: Theta(n log(n))
    // Short rationale for estimate: Collecting IDs takes Theta(n) and std::sort takes Theta(n log n) comparisons with average Theta(1) map lookups and distance calculations
    std::vector<StopID> stops_coord_order();

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Linear traversal through all stops in Stops_ to check name matches
    std::vector<StopID> find_stops(Name const& name);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::find and string assignment are average constant-time operations
    bool change_stop_name(StopID id, Name const& newname);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::find and Coord assignment are average constant-time operations
    bool change_stop_coord(StopID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::try_emplace provides average constant-time insertion
    bool add_region(RegionID id, Name const& name);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: std::unordered_map::find provides average constant-time key lookup
    Name get_region_name(RegionID id);

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Linear traversal through Regions_ map and copying IDs into a vector pre-allocated with reserve()
    std::vector<RegionID> all_regions();

    // Estimate of performance: Theta(1), O(ns + nr) where ns is number of stops and nr is number of regions
    // Short rationale for estimate: Constant-time map lookups with std::unordered_map::find and O(1) assignment and vector push_back
    bool add_stop_to_region(StopID id, RegionID parentid);

    // Estimate of performance: Theta(1), O(n)
    // Short rationale for estimate: Average constant-time map lookups with std::unordered_map::find, string assignment, and vector push_back
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: Theta(d), where d is the depth of the region hierarchy for the stop. O(n) if all regions happened to be in the same chain
    // Short rationale for estimate: Initial stop lookup takes average O(1), followed by traversing parent regions up the hierarchy chain where each region lookup takes average O(1)
    std::vector<RegionID> stop_regions(StopID id);

    // Estimate of performance: Theta(n)
    // Short rationale for estimate: Initial lookup takes average Theta(1). Traversing stops takes Theta(n) time, and std::partial_sort with a constant k=5 takes O(n log 5) = Theta(n) time
    std::vector<StopID> stops_closest_to(StopID id);

    // Estimate of performance: Theta(k), O(ns + nr), where k is number of stops in parent region, ns is total stops and nr is total regions
    // Short rationale for estimate: Map lookups and Stops_.erase take average Theta(1) time, but std::erase on the parent region's stops_ vector takes linear time Theta(k) relative to the number of stops in that region
    bool remove_stop(StopID id);

    // Estimate of performance: Theta(Sr + Rr), where Sr is total number of stops and Rr is total number of regions in the sub-tree
    // Short rationale for estimate: Calling get_region_coords takes Theta(Sr + Rr) time, and finding the min/max bounds requires a linear scan over the S_r collected coordinates
    std::pair<Coord, Coord> region_bounding_box(RegionID id);

    // Estimate of performance: Theta(d1 + d2), O(n), where d1 and d2 are the region hierarchy depths for id1 and id2, and n is total regions
    // Short rationale for estimate: Calling stop_regions takes Theta(d1) and Theta(d2) time. Inserting into and looking up from std::unordered_set takes average Theta(1) time per element
    RegionID stops_common_region(StopID id1, StopID id2);

    // Estimate of performance: Theta(s), O(s * ns + nr), where s is the number of stops on the route and ns is the total number of stops
    // Short rationale for estimate: Validating stops and updating each stop's routes_ vector takes average Theta(1) time per stop across s stops. Moving the vector into Routes_ takes O(1) time
    bool add_route(RouteID id, std::vector<StopID> stops);

    // Estimate of performance: Theta(n), where n is the number of routes
    // Short rationale for estimate: Linear traversal through Routes_ map and copying IDs into a vector pre-allocated with reserve()
    std::vector<RouteID> all_routes();

    // Estimate of performance: Theta(s * k), O(s * nr + ns), where s is the number of stops on the route, k is the average number of routes per stop, nr is total routes, and ns is total stops
    // Short rationale for estimate: Iterates through s stops on the route, performs average Theta(1) map lookup for each stop, and uses std::erase which takes linear Theta(k) time on the stop's routes_ vector
    bool remove_route(RouteID id);

    // Estimate of performance: Theta(Rs * Sr), worst-case O(Rs * Sr + ns), where Rs is the number of routes passing through the stop, Sr is the average number of stops on a route, and ns is total stops
    // Short rationale for estimate: Initial lookup takes average Theta(1). Iterates over Rs routes passing through the stop, performing an average Theta(1) map lookup and a linear std::find taking Theta(Sr) time for each route
    std::vector<std::pair<RouteID, StopID>> routes_from(StopID stopid);

    // Estimate of performance: Theta(n), O(n + nr) where n is the number of stops on route and nr is total routes
    // Short rationale for estimate: Finding the route takes average Theta(1) time and copying the vector of stops takes Theta(s) time
    std::vector<StopID> route_stops(RouteID id);

    // Estimate of performance: Theta(ns + nr) where ns is the number of stops and nr is the number of routes
    // Short rationale for estimate: Iterates over all ns stops to clear their routes_ vectors and calls clear() on Routes_ map which takes Theta(nr) time
    void clear_routes();

    // Estimate of performance: Theta(ns + C * Sr), worst-case O(ns + nr * Sr), where ns is the number of stops, C is the number of connections between stops, and Sr is the average route length
    // Short rationale for estimate: Performs a Breadth-First Search (BFS). At each node, routes_from takes O(nr * Sr) time, making the total edge traversal take O(C * Sr). Reconstructing the path and calculating distances takes O(k) time where k is the path length
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_any(StopID fromstop, StopID tostop);

//    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_least_stops(StopID fromstop, StopID tostop);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_with_cycle(StopID fromstop);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::tuple<StopID, RouteID, Distance>> journey_shortest_distance(StopID fromstop, StopID tostop);

private:
    // Rationale for chosen datastructures:


    // Stops_ (std::unordered_map<StopID, Stop_>):
    //  Chosen for average O(1) searching, insertion, deletion of stops by StopID.
    //  Iterating through unordered_map is linear in the number of elements.
    //  Inside Stop_:
    //    - routes_ (std::vector<RouteID>): Fast contiguous storage for routes passing through the stop.

    // Regions_ (std::unordered_map<RegionID, Region_>):
    //  Chosen for average O(1) access, insertion, and searching of regions by RegionID.
    //  Inside Region_:
    //    - stops_ (std::vector<StopID>) & subregions_ (std::vector<RegionID>):
    //       Sequential lists stored continuously for efficient traversal when building bounding boxes.

    // Routes_ (std::unordered_map<RouteID, std::vector<StopID>>):
    //  Provides average O(1) search for route data by RouteID.
    //  The std::vector<StopID> value maintains the order of stops along the route.

    // struct containing all info about stop
    struct Stop_ {
        StopID stopID_;
        RegionID regionID_ = NO_REGION;
        std::vector<RouteID> routes_;
        Name name_;
        Coord coord_;
    };

    // unordered_map holds all the stops for easy access to all stops through StopID without indexing
    std::unordered_map<StopID, Stop_> Stops_;

    // struct containing all info about region
    struct Region_ {
        RegionID regionID_ = NO_REGION;
        Name name_;
        std::vector<StopID> stops_;
        RegionID parent_ = NO_REGION;
        std::vector<RegionID> subregions_;
    };

    // unordered_map holds all the regions for easy access to all regions through RegionID without indexing
    std::unordered_map<RegionID, Region_> Regions_;

    // helper function to get all coords of stops in region
    void get_region_coords(RegionID id, std::vector<Coord>& coords);

    // helper function for DFS algorithm
    bool dfs_algo(StopID curr, std::vector<std::pair<StopID, RouteID>>& current_path, std::unordered_set<StopID>& visited, std::unordered_set<StopID>& in_stack);

    // unordered_map holds all the routes
    std::unordered_map<RouteID, std::vector<StopID>> Routes_;
};

#endif // DATASTRUCTURES_HH
