//
// Created by peau_c on 4/26/17.
//

#ifndef CPP_PLAZZA_PROCESSHANDLER_HPP
#define CPP_PLAZZA_PROCESSHANDLER_HPP


namespace plazza {
	class ProcessHandler : public IProcessHandler {
	public:
		ProcessHandler(size_t numberOfThreads, std::vector <command> commandList);
		~ProcessHandler();
		virtual void feed(const std::vector <command> commandList);
		
	};
}


#endif //CPP_PLAZZA_PROCESSHANDLER_HPP
