#include <QRegularExpression>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QApplication>
#include <QApplication>
#include <QStringList>
#include <QTcpSocket>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QFile>

int main (int argc, char *argv[]) {
	// Make a Qt application
	QCoreApplication app(argc, argv);
	
	// Set App Info
	QCoreApplication::setApplicationName("Qt TCP Socket");
	QCoreApplication::setApplicationVersion("1.1");

	// Add command line parser
	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addVersionOption();
	parser.setApplicationDescription("A light weight TCP request-socket maker.\nhttp://tridectet.ir");
	parser.addOptions({
		// Port option
		{{"p", "port"}, QCoreApplication::translate("main", "Set the port number"), QCoreApplication::translate("main", "Port")},
		// Url option
		{{"u", "url"}, QCoreApplication::translate("main", "Set the host address"), QCoreApplication::translate("main", "URL")},
		// Write
		{{"w", "write"}, QCoreApplication::translate("main", "Write the file data to the request socket"), QCoreApplication::translate("main", "Write")},
		// The Headers
		{"headers", QCoreApplication::translate("main", "Request headers file. Containing request-line for the http requests."), QCoreApplication::translate("main", "Headers")},
	});
	
	// Process the actual command line arguments given by the user
	parser.process(app);

	// Set URL if is set
	QString url = "tridectet.ir";
	if (parser.isSet("url")) url  = parser.value("url");
	
	// Set port if is set
	int port = 80;
	if (parser.isSet("port")) port = parser.value("port").toInt();
	
	// Make a socket, and connect to the host
	QTcpSocket * socket = new QTcpSocket();
	socket->connectToHost(url, port);
	printf("+ Made the socket successfully.\n+ Connecting to %s:%d...\n", url.toStdString().c_str(), port);
	
	// Has to connect in less that 5s
	if (socket->waitForConnected(5000)) {
		QString request_data;
                
		// Headers
		if(parser.isSet("headers")) {
			// Read headers file
			QFile headers_file(parser.value("headers"));
			if (headers_file.open(QFile::ReadOnly | QFile::Text)) {
				// Stream File
				QTextStream in(&headers_file);
				while (!in.atEnd()) {
					QString line = in.readLine();
					request_data.append(line.append("\r\n"));
				}
			}
			request_data.append("\r\n");
		}

		// Write File
		if(parser.isSet("write")) {
			// Read write file
			QFile write_file(parser.value("write"));
			if (write_file.open(QFile::ReadOnly | QFile::Text)) {
				// Stream file
				QTextStream in(&write_file);
				request_data.append(in.readAll());
			}
		}

		// Print Request Data
		printf("Request Data:\n%s\n", request_data.toStdString().c_str());

		// Write some data
		socket->write(request_data.toStdString().c_str());
		socket->waitForBytesWritten(1000);
		socket->waitForReadyRead(3000);
		
		// Working on the response
		QString response = socket->readAll();
		printf("+ Response [%ld]:\n%s", response.length(), response.toStdString().c_str());

        	// Close the socket.
        	socket->close();
	} else {
		qDebug() << "Not Connected";
	}

	// Run the app
	return app.exec();
}
