import java.util.HashMap;

public class Request {

    public enum Method {
        GET, POST
    }

    private String url;
    private Method method;

    public HashMap<String, Object> params= new HashMap<>();

    public Request (String url, Method method) {
        this.url = url;
        this.method = method;
    }

    public String getUrl() {
        return url;
    }

    public Method getMethod() {
        return method;
    }

}
