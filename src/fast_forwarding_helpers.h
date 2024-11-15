arma::mat create_Escape(const arma::mat& W, const arma::uvec& visited,
                        const arma::uvec& unvisited);

arma::mat create_PA(const arma::mat& W, const arma::uvec& visited);

arma::mat create_PA_Escape(const arma::mat& W, const arma::uvec& visited, const arma::uvec& unvisited);

arma::vec compute_x_Escape_A_solve(const arma::mat& P_A, const arma::mat& x_escape, const arma::uvec& ind);