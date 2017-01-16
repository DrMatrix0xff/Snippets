import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class HelloLogger {
    private static final Logger logger = LogManager.getLogger("HelloLogger");
    public static void main(String[] args) {
        logger.info("Hello, World!");
        logger.warn("may cause exception");
        logger.error("something really bad");
        logger.fatal("something extremely bad");
    }
}
