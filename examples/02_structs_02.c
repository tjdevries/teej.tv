// Memory layout for `coordinate`
//
//       +-----------------+
// field |  x  |  y  |  z  |
//       |-----|-----|-----|
// size  |  4  |  4  |  4  |
//       +-----------------+
//
// Now we have a `typedef` for `coordinate_t`
//  You can read `coordinate_t` as the "coordinate type" which
//  I think can be helpful for which location it lands in.
//
//  stdlib headers also use `_t`... but technically that means
//  they are all reserved LUL
//
//  coordinate_tj for your favorite professor?!
//
//  Oh well, we decide on this later, i will do `_t` for now.
typedef struct coordinate {
  int x;
  int y;
  int z;
} coordinate_t;

// Alternative method, forward declaring the struct
// (mention for recursive structs it's necessary?)
typedef struct coordinate_2 coordinate_2_t;
struct coordinate_2 {
  int x;
  int y;
  int z;
};

// not sure which is better....
//  I know it doesn't make a difference, but
//  I do want to pick one that is the same for the
//  entire course. Haven't decided yet.
//
// Also, yes, `other_struct` is optional as a name,
// but will probably keep it in there just for ease
// of reading and understanding
typedef struct other_struct {
  int x;
} OtherStruct;

int main() {
  // Create a new struct, using "designated initializers"
  // This time we can just say `coordinate_t`
  coordinate_t c = {.x = 1, .y = 2, .z = 3};

  OtherStruct o = {.x = 1};
}
