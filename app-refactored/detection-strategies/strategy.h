class Strategy {
public:
    virtual ~Strategy() {}
    virtual void execute(Deplacement &deplacement) = 0;
};