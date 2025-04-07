#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <limits>

const int MAX_DEPTH = 5; // Profondeur maximale de récursion

// Clamp pour valeurs RGB
float clamp(float x, float minVal, float maxVal) {
    return std::max(minVal, std::min(x, maxVal));
}

// -------------------- Classe vecteur --------------------
class vecteur {
public:
    float x, y, z;
    vecteur() : x(0), y(0), z(0) {}
    vecteur(float x, float y, float z) : x(x), y(y), z(z) {}

    vecteur operator+(const vecteur& v) const { return vecteur(x + v.x, y + v.y, z + v.z); }
    vecteur operator-(const vecteur& v) const { return vecteur(x - v.x, y - v.y, z - v.z); }
    vecteur operator*(float scalar) const { return vecteur(x * scalar, y * scalar, z * scalar); }
    float dot(const vecteur& v) const { return x * v.x + y * v.y + z * v.z; }
    vecteur cross(const vecteur& v) const {
        return vecteur(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
    vecteur normalize() const {
        float norm = std::sqrt(x*x + y*y + z*z);
        return (norm > 0) ? vecteur(x/norm, y/norm, z/norm) : vecteur(0,0,0);
    }
    // Rotation autour d'un axe (formule de Rodrigues)
    vecteur rotateAround(const vecteur &axis, float angle) const {
        vecteur k = axis.normalize();
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        return (*this) * cosA + k.cross(*this) * sinA + k * (k.dot(*this)) * (1 - cosA);
    }
};

// -------------------- Classe point --------------------
class point {
public:
    float x, y, z;
    point() : x(0), y(0), z(0) {}
    point(float x, float y, float z) : x(x), y(y), z(z) {}
    
    point operator+(const vecteur& v) const {
        return point(x + v.x, y + v.y, z + v.z);
    }
};

// -------------------- Classe rayon --------------------
class ray {
public:
    point origin;
    vecteur d;
    ray() : origin(point(0, 0, 0)), d(vecteur(0, 0, -1)) {}
    ray(point o, vecteur dir) : origin(o), d(dir.normalize()) {}
};

// -------------------- Classe materiel --------------------
class materiel {
public:
    vecteur couleur;
    float transparence; // 0 = opaque, 1 = complètement transparent
    materiel(vecteur c = vecteur(1, 1, 1), float t = 0) : couleur(c), transparence(t) {}
};

// -------------------- Classe Objet (base) --------------------
class Objet {
public:
    materiel mat;
    virtual ~Objet() = default;
    virtual bool intersect_ray(const ray& r, float& t, vecteur& normal) = 0;
};

// -------------------- Objets géométriques --------------------

// Sphere
class sphere : public Objet {
public:
    point center;
    float radius;
    sphere(point c, float r, materiel m) : center(c), radius(r) { mat = m; }
    bool intersect_ray(const ray& r, float& t, vecteur& normal) {
        vecteur oc = vecteur(r.origin.x - center.x, r.origin.y - center.y, r.origin.z - center.z);
        float a = r.d.dot(r.d);
        float b = 2.0f * oc.dot(r.d);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;
        t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        if (t < 1e-4f) return false;
        point hit_point = r.origin + r.d * t;
        normal = vecteur(hit_point.x - center.x, hit_point.y - center.y, hit_point.z - center.z).normalize();
        return true;
    }
};

// Plan (sol)
class plan: public Objet {
public:
    point p;
    vecteur normal;
    float size;
    plan(point pos, vecteur n, float s, materiel m) : p(pos), normal(n.normalize()), size(s) { mat = m; }
    bool intersect_ray(const ray& r, float& t, vecteur& hit_normal) {
        float denom = normal.dot(r.d);
        if (fabs(denom) > 1e-6) {
            vecteur p0l0 = vecteur(p.x - r.origin.x, p.y - r.origin.y, p.z - r.origin.z);
            t = p0l0.dot(normal) / denom;
            if (t < 1e-4f) return false;
            point hit_point = r.origin + r.d * t;
            if (fabs(hit_point.x - p.x) <= size / 2 && fabs(hit_point.z - p.z) <= size / 2) {
                hit_normal = normal;
                return true;
            }
        }
        return false;
    }
};

// Triangle
class triangle : public Objet {
public:
    point v0, v1, v2;
    vecteur normal;
    triangle(point p0, point p1, point p2, materiel m) 
        : v0(p0), v1(p1), v2(p2) {
        mat = m;
        normal = (vecteur(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z)
                .cross(vecteur(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z)))
                .normalize();
    }
    bool intersect_ray(const ray& r, float& t, vecteur& hit_normal) override {
        vecteur edge1 = vecteur(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
        vecteur edge2 = vecteur(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
        vecteur h = r.d.cross(edge2);
        float a = edge1.dot(h);
        if (fabs(a) < 1e-6) return false;
        float f = 1.0f / a;
        vecteur s = vecteur(r.origin.x - v0.x, r.origin.y - v0.y, r.origin.z - v0.z);
        float u = f * s.dot(h);
        if (u < 0.0f || u > 1.0f) return false;
        vecteur q = s.cross(edge1);
        float v = f * r.d.dot(q);
        if (v < 0.0f || (u + v) > 1.0f) return false;
        t = f * edge2.dot(q);
        if (t > 1e-4f) {
            hit_normal = normal;
            return true;
        }
        return false;
    }
};

// -------------------- Caméra avec orientation via vecteur --------------------
class camera {
public:
    int width, height;
    point position;
    vecteur orientation; // orientation.x = pitch, orientation.y = yaw, orientation.z = roll

    camera(int w, int h, point pos, vecteur orient = vecteur(0,0,0))
        : width(w), height(h), position(pos), orientation(orient) {}

    // Applique la rotation à un vecteur de direction
    vecteur apply_rotation(const vecteur &dir) const {
        vecteur rotated = dir;
        // Appliquer yaw (autour de Y)
        rotated = rotated.rotateAround(vecteur(0,1,0), orientation.y);
        // Appliquer pitch (autour de X)
        rotated = rotated.rotateAround(vecteur(1,0,0), orientation.x);
        // Appliquer roll (autour de Z)
        rotated = rotated.rotateAround(vecteur(0,0,1), orientation.z);
        return rotated;
    }

    // Génère les rayons à partir de la caméra en tenant compte de son orientation
    std::vector<std::vector<ray>> generate_rays() {
        std::vector<std::vector<ray>> rays(height, std::vector<ray>(width));
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                float u = (x - width / 2.0f) / width;
                float v = (y - height / 2.0f) / height;
                vecteur d = vecteur(u, v, -1).normalize();
                d = apply_rotation(d);
                rays[y][x] = ray(position, d);
            }
        }
        return rays;
    }
};

// -------------------- Fonction de trace récursive pour gérer la transparence --------------------
vecteur trace_ray(const ray &r,
                  const std::vector<std::unique_ptr<Objet>> &objets,
                  const point &light_source,
                  float ambient_intensity,
                  float intensity,
                  int depth)
{
    if (depth > MAX_DEPTH) return vecteur(0,0,0); // profondeur maximale atteinte

    float t_min = std::numeric_limits<float>::max();
    Objet* objet_proche = nullptr;
    vecteur normal_proche;

    // Recherche de l'objet le plus proche
    for (auto &obj : objets) {
        float t;
        vecteur n;
        if (obj->intersect_ray(r, t, n)) {
            if (t < t_min) {
                t_min = t;
                objet_proche = obj.get();
                normal_proche = n;
            }
        }
    }

    // Si aucun objet n'est intersecté, retourner la couleur du fond (ici noir)
    if (!objet_proche) {
        return vecteur(0,0,0);
    }

    // Calcul du point d'intersection
    point hit_point = r.origin + r.d * t_min;

    // Calcul de l'éclairage local (ombre et diffuse Lambert)
    vecteur to_light = vecteur(light_source.x - hit_point.x,
                               light_source.y - hit_point.y,
                               light_source.z - hit_point.z);
    float light_distance = std::sqrt(to_light.dot(to_light));
    vecteur light_dir = to_light.normalize();

    // Test d'ombre : lancer un rayon vers la lumière
    ray shadow_ray(hit_point + light_dir * 1e-4f, light_dir);
    bool in_shadow = false;
    for (auto &obj : objets) {
        float t_shadow;
        vecteur tmp_normal;
        if (obj->intersect_ray(shadow_ray, t_shadow, tmp_normal)) {
            if (t_shadow < light_distance) {
                in_shadow = true;
                break;
            }
        }
    }
    float diffuse = in_shadow ? 0.0f : std::max(0.0f, normal_proche.dot(light_dir)) * intensity;
    vecteur local_color = objet_proche->mat.couleur * (ambient_intensity + diffuse);

    // Gestion de la transparence
    float alpha = objet_proche->mat.transparence; // 0 opaque, 1 transparent
    if (alpha <= 0.0f) {
        // Objet opaque
        return local_color;
    } else {
        // Objet transparent, lancer un rayon "derrière" l'objet
        ray behind_ray(hit_point + r.d * 1e-4f, r.d);
        vecteur behind_color = trace_ray(behind_ray, objets, light_source, ambient_intensity, intensity, depth + 1);
        // Mélange simple : couleur locale atténuée par (1 - alpha) + couleur derrière * alpha
        return local_color * (1 - alpha) + behind_color * alpha;
    }
}

// -------------------- Fonction principale --------------------
int main() {
    int width = 800, height = 800;
    std::vector<vecteur> image(width * height);

    // Création de la caméra :
    // Position à (0, 1, 3) et orientation : ici, aucune rotation (orientation = (0,0,0))
    camera cam(width, height, point(0, 3, 1), vecteur(-10 * M_PI / 180, 0,0));
    //camera cam(width, height, point(0, 1, 3), vecteur(0,0,0));

    // Définition de quelques matériaux
    materiel mat_sol(vecteur(1, 1, 0), 0.0f);
    materiel mat_bleu(vecteur(0, 0, 1), 0.5f);
    materiel orange(vecteur(1, 0.5, 0), 0.0f);
    materiel rouge(vecteur(1, 0, 0), 0.5f);
    materiel mat_rouge(vecteur(1, 0, 0), 0.0f);

    // Création des objets
    std::vector<std::unique_ptr<Objet>> objets;
    objets.push_back(std::make_unique<plan>(point(0, 0, 0), vecteur(0, 1, 0), 100, mat_sol));
    objets.push_back(std::make_unique<sphere>(point(3, 2, -6), 0.5, mat_bleu));
    objets.push_back(std::make_unique<sphere>(point(1, 1, -5), 0.5, orange));
    objets.push_back(std::make_unique<sphere>(point(0, 1.1, -5), 1, rouge));
    
    objets.push_back(std::make_unique<sphere>(point(-1, 1.7, -3), 0.3, mat_rouge));
    objets.push_back(std::make_unique<triangle>(point(-1.5, 1, -2),point(-0.5, 1, -3),  point(-1.5, 2,-4), orange));
    // Pour tester la transparence, ajout d'une sphère orange derrière la sphère rouge transparente
    objets.push_back(std::make_unique<sphere>(point(0, 1, -10), 0.5, orange));

    // Paramètres de la lumière
    point light_source(0, 5, -3);
    float intensity = 1.0f;
    float ambient_intensity = 0.2f;

    // Génération des rayons de la caméra
    auto rays = cam.generate_rays();

    // Pour chaque pixel, on calcule la couleur via trace_ray
    //CUDA
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            vecteur color = trace_ray(rays[y][x], objets, light_source, ambient_intensity, intensity, 0);
            image[y * width + x] = color;
        }
    }

    // Sortie au format PPM
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            vecteur pixel = image[y * width + x];
            int r = static_cast<int>(clamp(pixel.x * 255, 0, 255));
            int g = static_cast<int>(clamp(pixel.y * 255, 0, 255));
            int b = static_cast<int>(clamp(pixel.z * 255, 0, 255));
            std::cout << r << " " << g << " " << b << "\n";
        }
    }
}
