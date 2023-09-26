#ifndef tp_qt_utils_Throttler_h
#define tp_qt_utils_Throttler_h

#include "tp_qt_utils/Globals.h"

#include <QObject>
#include <QTimer>

namespace tp_qt_utils
{

//##################################################################################################
class TP_QT_UTILS_SHARED_EXPORT Throttler: public QObject
{
  Q_OBJECT

public:
  //################################################################################################
  Throttler(int64_t timeOutMS);

  //################################################################################################
  virtual ~Throttler(){}

private:

  //################################################################################################
  void execNextStep();

  //################################################################################################
  virtual void step() = 0;

  //################################################################################################
  virtual bool finished() const = 0;

  QTimer m_timer;
  int m_timeOutMS;
};

//##################################################################################################
class TP_QT_UTILS_SHARED_EXPORT ThrottlerProcessVector : public Throttler
{
public:
  //################################################################################################
  ThrottlerProcessVector(std::size_t vecSize, std::size_t maxNToProcess, int64_t timeOutMS);

  //################################################################################################
  virtual ~ThrottlerProcessVector(){}
  
  //################################################################################################
  virtual bool finished() const override { return bool(m_offset >= m_vecSize); }

private:

  //################################################################################################
  virtual void step() override;

  //################################################################################################
  virtual void processChunk(std::size_t offset, std::size_t n) = 0;

  std::size_t m_vecSize, m_maxNToProcess, m_offset;
};
    
}
    
#endif