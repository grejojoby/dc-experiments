import java.rmi.*;
import java.rmi.server.*;

public class Add extends UnicastRemoteObject implements AddInterface {
    protected Add() throws RemoteException {
        super();
    }

    int num1, num2;

    public int sum(int n1, int n2) throws RemoteException {
        num1 = n1;
        num2 = n2;
        return num1 + num2;
    }
}
