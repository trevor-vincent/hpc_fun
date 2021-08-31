#include <vector>

// molecular.c
struct point{ double x,y; double mass; };
struct force{ double x,y; double f; };

/* Force on p1 from p2 */
struct force force_calc( struct point p1,struct point p2 ) {
  double dx = p2.x - p1.x, dy = p2.y - p1.y;
  double  f = p1.mass * p2.mass / sqrt( dx*dx + dy*dy );
  struct force exert = {dx,dy,f};
  return exert;
}

void add_force( struct force *f,struct force g ) {
  f->x += g.x; f->y += g.y; f->f += g.f;
}
void sub_force( struct force *f,struct force g ) {
  f->x -= g.x; f->y -= g.y; f->f += g.f;
}

void compute_forces(std::vector<force> &forces,
		    std::vector<point> &points)
{
  int N = forces.size();
  for (int ip=0; ip<N; ip++) {
    for (int jp=ip+1; jp<N; jp++) {
      struct force f = force_calc(points[ip],points[jp]);
      add_force(&forces[ip],f);
      sub_force(&forces[jp],f);
    }
  }
}

int main(int argc, char *argv[])
{
  int num_particles = 10;
  std::vector<point> points(num_particles);
  std::vector<force> forces(num_particles, {0,0,0});

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);

  for (int i = 0; i < num_particles; i++){
    point & p = points[i];
    p.x = distribution(generator);
    p.y = distribution(generator);
    p.c = 1.0;
  }
  
  return 0;
}
