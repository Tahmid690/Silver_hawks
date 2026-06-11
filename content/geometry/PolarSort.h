/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Sort points, works even if three points are collinear
 * Status: Works fine, used a lot
 */
inline int quad (point p) {
  if (p.x < 0 and p.y < 0) return 0;
  if (p.x >= 0 and p.y < 0) return 1;
  if (p.x >= 0 and p.y >= 0) return 2;
  if (p.x < 0 and p.y >= 0) return 3;
}

sort(v.begin(), v.end(), [] (point a, point b) {
  return quad(a) == quad(b) ? a.x * b.y > a.y * b.x : quad(a) < quad(b);
});