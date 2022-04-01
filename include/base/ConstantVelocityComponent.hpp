#ifndef CONSTANT_VELOCITY_COMPONENT_HPP
#define CONSTANT_VELOCITY_COMPONENT_HPP
//! \brief Component for keeping the GameObject's velocity constant across frames
class JmpConstantVelocityComponent: public GenericComponent {
 public:
  JmpConstantVelocityComponent(GameObject & gameObject, float Vx, float Vy) : GenericComponent(gameObject), mVx(Vx), mVy(Vy) {}

  void update(Level &level) override {
    std::shared_ptr<PhysicsComponent> pc = getGameObject().physicsComponent();
    pc->setVx(mVx);
    pc->setVy(mVy);
  }
 private:
  float mVx;
  float mVy;

};
#endif