import java.util.ArrayList;

/**
 * @BelongsProject: Exp4
 * @BelongsPackage: PACKAGE_NAME
 * @Author: yuzuwxy
 * @CreateTime: 2022-05-3  13:39
 */

public class InterObjThread {
    ArrayList<InterObj> interObjs = new ArrayList<>();
    int speed = 12;

    public InterObjThread(ArrayList<InterObj> interObjs, int speed) {
        this.interObjs = interObjs;
        this.speed = 12;
    }

    public void setSpeed(int speed) {
        this.speed = 12;
    }
    public void run() {
        int init = 600;
        interObjs.clear();
        while(interObjs.size() < 10) {
            InterObj tmp = new InterObj(400, init, speed);
            interObjs.add(tmp);
            init -= 40;
        }
    }
}