/*
** File description:
** main
*/

#include <Plugin/MultiCouple.hh>
#include <Wrapper/WrapperMultiCouple.hh>

std::vector<double> Wrapper::simulate_multi_couple(double *tab_init_1D,
                                            int R,
                                            double kernel_mu,
                                            double kernel_sigma,
                                            double *bs,
                                            double *ms,
                                            double *ss,
                                            double time,
                                            int width,
                                            int height,
                                            int nb_couple,
                                            int *nb_rings)
{
    std::vector<std::vector<double>> tab_init_2d{};
    std::vector<double> return_value{};
    std::vector<std::vector<double>> bs_vec{};
    int idx = 0;
    std::vector<double> ms_vec{};
    std::vector<double> ss_vec{};

    for (size_t j{0}; j < height; j++) {
        size_t checkpoint{j * width};
        std::vector<double> tmp{};
        for (size_t i{0}; i < width; i++) {
            tmp.emplace_back(tab_init_1D[i + checkpoint]);
        }
        tab_init_2d.emplace_back(tmp);
        tmp.clear();
    }
    for (size_t i{0}; i < nb_couple; i++) {
        std::vector<double> tmp{};
        for (size_t j{0}; j < nb_rings[i]; j++) {
            tmp.emplace_back(bs[j + idx]);
        }
        idx += nb_rings[i];
        bs_vec.emplace_back(tmp);
        tmp.clear();
    }
    for (size_t i{0}; i < nb_couple; i++) {
        ms_vec.emplace_back(ms[i]);
        ss_vec.emplace_back(ss[i]);
    }

    PLC::MultiCouple multi_couple{tab_init_2d, R, kernel_mu, kernel_sigma, bs_vec, ms_vec, ss_vec, time};
    multi_couple.run();
    std::vector<std::vector<double>> simult_result{multi_couple.getTab()};
    for (auto vec : simult_result) {
        for (size_t i{0}; i < vec.size(); i++)
            return_value.emplace_back(vec[i]);
    }

    return return_value;
}
