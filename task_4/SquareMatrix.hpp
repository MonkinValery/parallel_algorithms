class SquareMatrix
{
    private:
        double** squareMatrix;
        int N;
    public:
        SquareMatrix(int);
        ~SquareMatrix();
        double getElement(int, int);
        void setElement(int, int, double);
        void printToConsole();
        void printElement(int, int);
};

