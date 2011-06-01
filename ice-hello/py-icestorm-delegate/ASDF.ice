module ASD  {
  interface Listener {
    void adv(string name);
  };

  interface ASDA {
    void addListener(ASD::Listener* listener);
    Listener* getPublisher();
  };
};
