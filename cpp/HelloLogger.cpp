#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>

int main(int argc, char *argv[]) {
    log4cpp::OstreamAppender *handler = new log4cpp::OstreamAppender("StreamHandler", &std::cerr);
    log4cpp::PatternLayout *fmtter = new log4cpp::PatternLayout();
    fmtter->setConversionPattern("[%c %p %d{%y%m%d %H:%M:%S} ] -- %m%n");
    handler->setLayout(fmtter);

    log4cpp::Category& logger = log4cpp::Category::getRoot();
    logger.addAppender(handler);
    logger.setPriority(log4cpp::Priority::INFO);

    logger.info("This is normal");
    logger.warn("Something bad, but not enough");
    logger.error("Something really bad");
    logger.fatal("Something extremely bad");

    log4cpp::Category::shutdown();

    return 0;
}

