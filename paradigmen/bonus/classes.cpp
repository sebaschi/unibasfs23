#include <iostream>
#include <string>
#include <algorithm>

typedef double size;
typedef double mass;
typedef double angle;
typedef double relative;

class Bodypart {

    public:
        std::string name;
        size   height, length, width;
        mass   weight;
        angle  rot_x,  rot_y,  rot_z;

        

        Bodypart(size height=0, size length=0, size width=0, mass weight=0) {

            this->height = height;
            this->length = length;
            this->width  = width;
            this->weight = weight;

            rot_x = rot_y = rot_z = 110;

        }

        virtual ~Bodypart() {}

        virtual angle* canMove() {
            angle arr[3] = {rot_x, rot_y, rot_z};
            return arr;
        }

        std::string getName() { return name; }
        size getHeight() { return height; }
        size getLength() { return length; }
        size getWidth() { return width; }
        mass getWeight() { return weight; }
};

class Animal {

    protected:
        static int counter;
        std::string     name;
        Bodypart   head, torso, *limbs;
        int        number_of_limbs;
        double     weight, height, length;

    public:

        Animal(): name("not even a name"), 
                  limbs(nullptr), number_of_limbs(0), 
                  weight(0), height(0), length(0){counter++;}

        virtual ~Animal() {}

        std::string WhoAmI() { return name; }

        virtual void move ( relative speed) = 0; 

        /* Looking at definition of canMove, it seems 0 is for x, 1 for y, 2 for z */
        virtual void turn ( relative* dir) {

            angle rot_x = std::max(std::max(limbs[0].canMove()[0],
                        limbs[1].canMove()[0]),
                    std::max(limbs[2].canMove()[0],
                        limbs[3].canMove()[0]));
            angle rot_y = std::max(std::max(limbs[0].canMove()[1],
                        limbs[1].canMove()[1]),
                    std::max(limbs[2].canMove()[1],
                        limbs[3].canMove()[1])); 
            angle rot_z = std::max(std::max(limbs[0].canMove()[2],
                        limbs[1].canMove()[2]),
                    std::max(limbs[2].canMove()[2],
                        limbs[3].canMove()[2]));

            std::cout << "Turning towards (" << rot_x * dir[0]
                      << ", " << rot_y * dir[1]
                      << ", " << rot_z * dir[2] << ")" << std::endl;
        }

        virtual void look_at(relative* target) {

            std::cout << "Looking at "
                      << "(" << head.canMove()[0] * target[0]
                      << ", " << head.canMove()[1] * target[1]
                      << ", " << head.canMove()[2] * target[2] << ")"
                      << ")" << std::endl;
        }

        void be_born() {
            std::cout << "I'm alive" << std::endl;
        }

        void die() {
            std::cout << "No Comment!" << std::endl;
        }

        mass getHeadWeight() { return head.getWeight(); }

        double getRightFootHeight() {

            if (number_of_limbs < 4) {
                return 0;
            } else {
                return limbs[2].getHeight();
            }
        }
};

int Animal::counter = 0;

class Cat: public Animal {

    class CatBodyPart: public Bodypart {

        double feline_rot_x = 170, 
               feline_rot_y = 170, 
               feline_rot_z = 170;

        public: 

            CatBodyPart(size height, size length, 
                        size width , mass weight):

                   Bodypart( 0.9 * height
                            , 0.9 * length
                            , 0.9 * width
                            , 0.9 * weight) {}

            ~CatBodyPart() {}

            angle* canMove() {
                return new angle[3]{feline_rot_x, feline_rot_y, feline_rot_z};
            }

    };

    public:

        CatBodyPart* limbs;
        CatBodyPart head;
        CatBodyPart torso;

        Cat(): Animal(), head(0.9, 0.9, 0.9, 0.9), torso(0.9, 0.9, 0.9, 0.9) {

            name = "Cat";

            number_of_limbs = 4;
            limbs = new CatBodyPart[4]{CatBodyPart(3.0, 9.0, 2.0, 1.4),
                     CatBodyPart(3.0, 9.0, 2.0, 1.4),
                     CatBodyPart(3.0, 9.0, 2.0, 1.4),
                     CatBodyPart(3.0, 9.0, 2.0, 1.4)};

        }

        ~Cat() {
            delete[] limbs;
        }


        void move( relative speed) {
            std::cout << "I (" << WhoAmI()
                      << " ) am running at "
                      << 30 * speed << std::endl;
        }

        void die() {
            std::cout << "Still six to go..." << std::endl;
        }
};

class Dog: public Animal {

    public:

        Dog(): Animal() {
            
            name     = "Dog";
            number_of_limbs = 4;
            limbs = new Bodypart[4]{ Bodypart( 5.0, 12.0, 2.0, 2.1) ,
                       Bodypart( 5.0, 12.0, 2.0, 2.1) ,
                       Bodypart( 5.0, 13.0, 2.0, 2.1) ,
                       Bodypart( 5.0, 13.0, 2.0, 2.1) };
        }
        
        ~Dog() {delete[] limbs;}

        void move(relative speed) {
            std::cout << "I (" << WhoAmI()
                      << " ) am running at "
                      << 40 * speed << std::endl;
        }
};

class Snail: public Animal {

    public: 

        Snail(): Animal() {name = "Snail";}

        ~Snail() {};

        std::string WhoAmI() { return "Speed Racer";
        }

        void move( relative speed) {
            std::cout << "I (" << WhoAmI()
                      << " ) am running at "
                      << 0.1 * speed << std::endl;
        }
};

void focus(Animal* ani) {ani->look_at(new relative[3]{0.0, 0.0, 0.0});}

int main() {


    Animal* myZoo[4];

    myZoo[0] = new Cat();
    myZoo[1] = new Dog();
    myZoo[2] = new Snail(); /* Invalid because Animal is pure abstract */

    std::cout << "Why cats climb trees :" << std::endl;
    myZoo[0]->move(1.0);
    myZoo[1]->move(1.0);
    std::cout << std::endl;

    focus((myZoo[0]));
    focus((myZoo[1]));

    myZoo[0]->turn(new relative[3]{1.0, 0.0, 0.0});
    myZoo[1]->turn(new relative[3]{1.0, 0.0, 0.0});

    myZoo[3]->WhoAmI(); //Segfault, since uninitialized
    (static_cast<Snail*>(myZoo[3]))->WhoAmI();

    return (0);

}
        
