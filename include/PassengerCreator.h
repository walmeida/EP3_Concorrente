#ifndef PASSENGERCREATOR_H_
#define PASSENGERCREATOR_H_

class PassengerCreator : public Thread {
    private:
       const float PROPORCAO = 0.3; 
    public:
        PassengerCreator ();
        ~PassengerCreator ();
};

#endif // PASSENGERCREATOR_H_
