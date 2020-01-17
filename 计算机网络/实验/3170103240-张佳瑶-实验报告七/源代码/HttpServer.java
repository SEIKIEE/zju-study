import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class HttpServer {
    private ServerSocket listener;
    private final short PORT = 3240;

    /**
     * 启动服务器
     */
    public HttpServer() {
        try {
            listener = new ServerSocket(PORT);
            System.out.println("服务器开始工作");
            Socket socket = null;
            while (true) {
                socket = listener.accept();
                System.out.println("收到一个socket");
                ServerThread myThread = new ServerThread(socket, "./content");
                System.out.println("client host address:" + socket.getInetAddress().getHostAddress());
                myThread.start();
            }
        } catch (IOException e) {
            System.out.println(e);
        }
    }

}

/**
 * 服务端接受信息并处理的线程
 */
class ServerThread extends Thread {
    private Socket socket;
    private BufferedReader br;
    private OutputStream pw;
    private String msg;
    private String root;
    private static final int BUFFER_SIZE = 4096;
    private static final String LOGIN = "zjy";
    private static final String PSW = "htt";

    public ServerThread(Socket s, String file) throws IOException {
        socket = s;
        root = file;
        br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        pw = socket.getOutputStream();
    }

    @Override
    public void run() {
        System.out.println("host address " + socket.getInetAddress().getHostAddress() + " thread begins to work");
        Request request = getHttpHeader();
        if (request != null) {
            try {
                if (request.getMethod() == Request.Method.GET) {
                    responseGET(request.getUrl());
                } else if (request.getMethod() == Request.Method.POST) {
                    responsePOST(request);
                } else throw new Exception("Method " + request.getMethod() + " not supported!");
                System.out.println(Thread.currentThread().getName() + ": 执行结束...");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * 获取请求头
     *
     * @return 请求头
     */
    private Request getHttpHeader() {
        try {
            msg = br.readLine();
            String[] list = msg.split(" ");
            System.out.println(msg);
            if (list.length != 3)
                throw new Exception("http request header error");
            Request request = new Request(list[1], Request.Method.valueOf(list[0].trim()));
            if (request.getMethod() == Request.Method.POST) {
                int contentLength = 0;
                while ((msg = br.readLine()) != null) {
                    if ("".equals(msg)) {   //判断是否读到请求头末尾
                        break;
                    } else if (msg.contains("Content-Length")) {  //计算长度
                        contentLength = Integer.parseInt(msg.substring(msg.indexOf("Content-Length") + 16));
                    }
                }
                char[] buf;
                if (contentLength != 0) {
                    buf = new char[contentLength];
                    br.read(buf, 0, contentLength);
                    String[] params = new String(buf).split("&");  //分割键值对
                    for (String item : params) {
                        String key = item.substring(0, item.indexOf("="));  //获取键值对
                        String val = item.substring(item.indexOf("=") + 1);
                        request.params.put(key, val);
                    }
                }
            }
            return request;
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 响应GET方式请求
     *
     * @param filepath 响应的文件路径
     */
    private void responseGET(String filepath) throws IOException {
        File file = new File(root, filepath);
        System.out.println(socket.getInetAddress().getHostAddress() + " requests " + file.getName());
        if (!filepath.equals("/") && file.exists()) {  //文件存在
            String extension;
            InputStream in = new FileInputStream(file);
            byte[] bytes = new byte[BUFFER_SIZE];  //缓冲区
            int len;  //每次读入缓冲区的长度
            pw.write("HTTP/1.1 200 OK\r\n".getBytes());
            extension = filepath.substring(filepath.lastIndexOf("."));  //获取文件扩展名
            if (extension.equals(".jpg")) {  //设置MIME消息类型
                pw.write("content-type:image/jpg\r\n".getBytes());
            } else if (extension.equals(".html")) {
                pw.write("content-type:text/html;charset=UTF-8\r\n".getBytes());
            } else {
                pw.write("content-type:text/plain;charset=UTF-8\r\n".getBytes());
            }
            pw.write("\r\n".getBytes());
            while ((len = in.read(bytes)) != -1) {  //输出资源
                pw.write(bytes, 0, len);
            }
            pw.flush();
            pw.close();
        } else {  //文件不存在
            String err = "HTTP/1.1 404 file not found \r\n" + "Content-Type:text/html;charset=UTF-8\r\n" +
                    "Content-Length:22 \r\n" + "\r\n" + "<h1>404 Not Found</h1>";
            pw.write(err.getBytes()); //输出字节流
            pw.flush();
            pw.close();
        }
    }

    private void responsePOST(Request request) throws IOException {
        if (request.getUrl().equals("/dopost") && request.params.containsKey("login") && request.params.containsKey("pass")) {
            String msg;
            String login = (String) request.params.get("login");
            String pass = (String) request.params.get("pass");
            if (login.equals(LOGIN) && pass.equals(PSW))
                msg = "<html><head><meta charset=\"UTF-8\"></head><body>登录成功!</body></html>";
            else msg = "<html><head><meta charset=\"UTF-8\"></head><body>登录失败!</body></html>";
            msg = "HTTP/1.1 200 OK\r\n" + "Content-Type:text/html \r\n" +
                    "Content-Length:" + msg.length() + "\r\n" + "\r\n" + msg;
            pw.write(msg.getBytes()); //输出字节流
            pw.flush();
            pw.close();
        } else {
            String err = "HTTP/1.1 404 file not found \r\n" + "Content-Type:text/html \r\n" +
                    "Content-Length:22 \r\n" + "\r\n" + "<h1>404 Not Found</h1>";
            pw.write(err.getBytes()); //输出字节流
            pw.flush();
            pw.close();
        }
    }
}

